#include "WebAPI.hpp"
#include <QEventLoop>
#include <CkHttp.h>
#include <CkHttpResponse.h>
#include <CkHttpRequest.h>
#include <CkJsonArray.h>
#include <AppDefines.h>
#include <QUrl>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <iostream>
#include <CkCrypt2.h>
#include <string>
#include <QFile>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <CkBinData.h>

#define MODEL AppModel::instance()

static QJsonObject deviceInfo;
const char * token = "100KMJAPZX62L";


WebAPI* WebAPI::s_instance = nullptr;

WebAPI::WebAPI(QObject *parent) : QObject(parent)
{
    // Do nothing
    deviceInfo["AndroidId"] = "DESKTOP";
    deviceInfo["IMEI"] = "IMEI";
}

WebAPI *WebAPI::instance()
{
    if(s_instance == nullptr){
        s_instance = new WebAPI();
    }
    return s_instance;
}

std::string hashKey(const std::string &input, int blockSize)
{
    std::string result;
    if (input.length() >= blockSize && 32 % blockSize == 0)
    {
        for (int i = 0; i < 32 / blockSize; i++)
        {
            if (i + blockSize < input.length())
            {
                result += input.substr(i, blockSize);
            }
            else
            {
                result += input.substr(input.length() - blockSize, blockSize);
            }
        }
    }
    return result;
}

std::string hashIv(const std::string &input, int blockSize)
{
    std::string result;
    if (input.length() >= blockSize && 16 % blockSize == 0)
    {
        for (int i = 0; i < 16 / blockSize; i++)
        {
            if (i + blockSize < input.length())
            {
                result += input.substr(i, blockSize);
            }
            else
            {
                result += input.substr(input.length() - blockSize, blockSize);
            }
        }
    }
    return result;
}

std::pair<std::string, std::string> WebAPI::getDynamicKey() {
    std::pair<std::string, std::string> output;
    std::string currTime = getCurrentTime();
    std::string outputKey = std::string(KEY_PREFIX) + currTime + currTime;
    outputKey = outputKey.substr(0,32);
    output.first = outputKey;
    output.second = currTime;
    return output;
}

QString WebAPI::md5(QString input) {
    CkCrypt2 crypt;
    // The desired output is a hexidecimal string:
    crypt.put_EncodingMode("hex");
    // Set the hash algorithm:
    crypt.put_HashAlgorithm("md5");

    return crypt.hashStringENC(input.toUtf8().data());
}

std::string WebAPI::getCurrentTime() {
    std::string output;
    time_t t;
    struct tm *tmp;
    t = time(nullptr);
    tmp = gmtime(&t);

    char buffer[20];
    snprintf(buffer,20,"%4d:%02d:%02d:%02d:%02d:%02d",(tmp->tm_year + 1900), (tmp->tm_mon + 1), tmp->tm_mday, tmp->tm_hour, tmp->tm_min, tmp->tm_sec);
    output = std::string(buffer);
    return output;
}

std::string getKeyFromTimestamp(const std::string &timeStamp)
{
    std::string key = std::string(KEY_PREFIX) + timeStamp + timeStamp;
    return key.substr(0, 32);
}

std::string WebAPI::getEncodedString(std::string input, std::string key) {
    return this->encrypt(input.data(), key.data(), this->getIv());
}

std::string WebAPI::encrypt(const char *input, const char *key, const char *iv) {
    if (input == nullptr)
        return "";
    if (key == nullptr)
        return "";
    if (iv == nullptr)
        return "";

    CkCrypt2 crypt;

    crypt.put_CryptAlgorithm("aes");
    crypt.put_CipherMode("cbc");
    crypt.put_KeyLength(256);
    crypt.put_PaddingScheme(0);
    crypt.put_EncodingMode("base6");
    crypt.SetEncodedIV(iv, "ascii");
    crypt.SetEncodedKey(key, "ascii");
    return std::string(crypt.encryptStringENC(input));
}

std::string WebAPI::decrypt(const char *input, const char *key, const char *iv) {
    if (input == nullptr)
        return "";
    if (key == nullptr)
        return "";
    if (iv == nullptr)
        return "";

    CkCrypt2 crypt;

    crypt.put_CryptAlgorithm("aes");
    crypt.put_CipherMode("cbc");
    crypt.put_KeyLength(256);
    crypt.put_PaddingScheme(0);
    crypt.put_EncodingMode("base6");
    crypt.SetEncodedIV(iv, "ascii");
    crypt.SetEncodedKey(key, "ascii");
    return std::string(crypt.decryptStringENC(input));
}

std::string WebAPI::encryptTimestamp(const std::string &timestamp, const std::string &token)
{
    std::string keyFromToken = hashKey(token, 8);
    std::string ivFromToken = hashIv(token, 4);
    return encrypt(timestamp.data(), keyFromToken.data(), ivFromToken.data());
}

std::string WebAPI::decryptTimestamp(const std::string &timestamp, const std::string &token)
{
    std::string keyFromToken = hashKey(token, 8);
    std::string ivFromToken = hashIv(token, 4);
    return decrypt(timestamp.data(), keyFromToken.data(), ivFromToken.data());
}

const char * WebAPI::getIv() {
    return "Congaubeo@123560";
}

bool WebAPI::sendRequest(QJsonObject &bodyData, QJsonObject &response, const char *api, QMap<QString, QString> headers = QMap<QString,QString>())
{
    bool success = false;
    QString url = QString("http://95.179.130.172/cgi-bin/autofarmer.api?api=%1&token=%2").arg(api).arg(token);
    LOGD << "url: " << url;
    bodyData["device_info"] = deviceInfo;
    bodyData["token"] = token;

    KEY_PAIR keyPair = getDynamicKey();
    std::string enData = encrypt(QJsonDocument(bodyData).toJson(QJsonDocument::Compact).data(), keyPair.first.data(), WebAPI::getIv());
    std::string enClientTimestamp = encryptTimestamp(keyPair.second, token);

    QJsonObject jsonReqBody;
    jsonReqBody["data"] = enData.data();
    jsonReqBody["client_timestamp"] = enClientTimestamp.data();

    CkHttp http;
    http.put_ConnectTimeout(30);
    http.put_ReadTimeout(30);
    http.SetRequestHeader("Content-Type", "application/json");
    http.SetRequestHeader("mobile-secret-key", md5(token).toUtf8().data());
    foreach(QString key , headers.keys()) {
        LOGD << "Header--> " << key << ":" << headers.value(key);
        http.SetRequestHeader(key.toUtf8().data(), headers.value(key).toUtf8().data());
    }

    CkHttpResponse *resp = http.PostJson(url.toUtf8().data(), QJsonDocument(jsonReqBody).toJson(QJsonDocument::Compact).data());

    if (!http.get_LastMethodSuccess())
    {
        LOGD << "Error: " <<  http.lastErrorText();
    }
    else
    {
        if (resp->bodyStr())
        {
            QJsonObject jsonResponse = QJsonDocument::fromJson(resp->bodyStr()).object();
                            if (!jsonResponse.isEmpty())
                            {
                                if (jsonResponse.contains("data"))
                                {
                                    if (jsonResponse.contains("server_timestamp"))
                                    {
                                        std::string serverTimeStamp = jsonResponse["server_timestamp"].toString().toStdString();
                                        serverTimeStamp = decryptTimestamp(serverTimeStamp, token);
                                        LOGD << "serverTimeStamp: " << serverTimeStamp.data();
                                        std::string key = getKeyFromTimestamp(serverTimeStamp);
                                        QString data = decrypt(jsonResponse["data"].toString().toUtf8().data(), key.data(), WebAPI::getIv()).data();

                                        QJsonObject responseData = QJsonDocument::fromJson(data.toUtf8().data()).object();

                                        if (!responseData.isEmpty())
                                        {
                                            if (responseData.contains("data"))
                                            {
                                              QJsonObject server_data = QJsonDocument::fromJson(responseData["data"].toString().toUtf8()).object();
                                                if (!server_data.isEmpty())
                                                {
                                                    if (server_data.contains("data"))
                                                    {
                                                        QString data = server_data["data"].toString();
                                                        server_data["data"] = QString::fromUtf8(QByteArray::fromBase64(data.toUtf8()));
                                                    }
                                                    response["data"] = server_data;
                                                }
                                            }

                                            response["cgi_message"] = responseData["cgi_message"].toString();
                                            response["response_code"] = responseData["response_code"].toInt();
                                            response["success"] = responseData["success"].toBool();
                                            success = true;
                                        }
                                    }
                                    else
                                    {
                                        LOGD << "error_message", "Could not get server_timestamp";
                                    }
                                }
                                else
                                {
                                    LOGD << "Data field is not existed!";
                                }
                            }
                            else
                            {
                                LOGD << "Could not load resp->bodyStr() -> JsonObject";
                            }
        }
        else
        {
            LOGD << "error_message", "resp->bodyStr() is NULL";
        }
    }
    delete resp;
    return success;
}


void WebAPI::getJasmineLog(QList<QJsonObject> &dataContainer)
{
    LOGD << "";
    QString url = "https://log.autofarmer.xyz/api/Jasmine";
    QJsonObject json;

    json.insert("action", "GetJasmine");
    json.insert("token", "496UTSHK4XMCNV1WEYP41K");

    QByteArray jsonData = QJsonDocument(json).toJson();

    CkHttpRequest req;
    CkHttp http ;
    http.put_Utf8(true);
    http.SetRequestHeader("Content-Type","application/json");

    CkHttpResponse *resp = nullptr;
    resp = http.PostJson2(url.toLocal8Bit().data(), "application/json", jsonData.data());
    if (http.get_LastMethodSuccess() != true) {
        LOGD << "Http error: " + QString(http.lastErrorText());
    } else {
        if (resp->bodyStr()) {
            CkJsonObject jsonResponse;
            jsonResponse.put_Utf8(true);
            bool loadJson = jsonResponse.Load(resp->bodyStr());
            if (loadJson) {
                CkJsonArray* dataArr = jsonResponse.ArrayOf("data");
                if(dataArr) {
                    LOGD << "dataArr: " << dataArr->get_Size();
                    for(int i = 0; i < dataArr->get_Size(); i++ ){
                        CkJsonObject* recordObj = dataArr->ObjectAt(i);
                        QJsonObject recordQObj;
                        recordQObj["token"] = recordObj->stringOf("token");
                        recordQObj["dateTime"] = recordObj->stringOf("dateTime");
                        recordQObj["info"] = recordObj->stringOf("info");
                        recordQObj["devicename"] = recordObj->stringOf("devicename");
                        recordQObj["module"] = recordObj->stringOf("module");
                        recordQObj["tag"] = recordObj->stringOf("tag");
                        recordQObj["page"] = recordObj->stringOf("page");
                        recordQObj["message"] = recordObj->stringOf("message");
                        recordQObj["screenInfo"] = recordObj->stringOf("screeninfo");
                        dataContainer.append(recordQObj);
                    }
                    LOGD << "dataContainer: " << dataContainer.size();
                }
            } else {
                LOGD << "Could not load resp->bodyStr() -> JsonObject";
            }
        } else {
            LOGD << "resp->bodyStr() is NULL";
        }
    }
    LOGD << "DONE";
}

void WebAPI::getJamineDefinations(QString &definations)
{
    LOGD << "";
    QJsonObject bodyData, response;
    bodyData["action"] = "GetJasmine";

    if (sendRequest(bodyData, response, "config"))
    {
        QJsonObject server_data = response["data"].toObject();
        if (server_data.contains("data"))
        {
            definations = server_data["data"].toString();
            return;
        }
    }
    LOGD << "response: " << response;
}

void WebAPI::saveJamineDefinations(QJsonArray &defArr)
{
    QString defArrStr = QJsonDocument(defArr).toJson();
    LOGD << "";
    QString url = "https://api4.autofarmer.xyz/api4/config?token=496UTSHK4XMCNV1WEYP41K";
    QJsonObject json;

    /*
    QString content;
    QFile bkFile("../../../../PDT/DataBackup/jasmine.json");
    if (bkFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        content = bkFile.readAll();
        if(!content.isNull() && !content.isEmpty()){
            json.insert("data", this->getEncodedString(std::string(content.toUtf8().toBase64()),keyPair.first).data());
        }
    }
    */

    QString bkFileName = "../../../../PDT/DataBackup/" + \
            QString::number(QDate::currentDate().year()) + "-" + \
            QString::number(QDate::currentDate().month() + 1) + "-" + \
            QString::number(QDate::currentDate().day()) + "-" + \
            QString::number(QTime::currentTime().hour()) + "-" + \
            QString::number(QTime::currentTime().minute()) + ".json";

    QFile jsonFile(bkFileName);
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(QJsonDocument(defArr).toJson());
    jsonFile.close();

    QJsonObject bodyData, response;
    bodyData["action"] = "SaveJasmine";
    bodyData["jasmine_data"] = QString(defArrStr.toUtf8().toBase64());

    QMap<QString,QString> header;
    header.insert("save-jasmine-secret-key","0b21335f-f715-40e1-b312-b099cd87ec4e");
    sendRequest(bodyData, response, "config",header);
    LOGD << "response: " << response;
}



