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
#include <CkCert.h>
#include <CkPrivateKey.h>
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
    deviceInfo["MacAddress"] = "XXXXXXXXXXX";
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
    QString url = QString("https://api5.autofarmer.net/cgi-bin/autofarmer5.api?api=%1&token=%2").arg(api).arg(token);
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

    CkCert cert;
    CkPrivateKey privKey;

    // Load any type of certificate (.cer, .p7b, .pem, etc.) by calling LoadFromFile.
    success = cert.LoadPem("-----BEGIN CERTIFICATE-----\
                           MIID/zCCAuegAwIBAgIDEAACMA0GCSqGSIb3DQEBCwUAMHcxCzAJBgNVBAYTAlVT\
                           MRMwEQYDVQQIDApTb21lLVN0YXRlMRcwFQYDVQQKDA5BdXRvRmFybWVyIEx0ZDET\
                           MBEGA1UEAwwKQXV0b0Zhcm1lcjElMCMGCSqGSIb3DQEJARYWY2FAYXBpNS5hdXRv\
                           ZmFybWVyLm5ldDAeFw0yMTA1MjQxMDA1MzlaFw0zMTA1MjIxMDA1MzlaMIGEMQsw\
                           CQYDVQQGEwJVUzEcMBoGA1UECBMTU3RhdGUgb3IgUHJvdmlkZW5jZTEQMA4GA1UE\
                           ChMHQ29tcGFueTEcMBoGA1UEAxMTYXBpNS5hdXRvZmFybWVyLm5ldDEnMCUGCSqG\
                           SIb3DQEJARYYYXBpNUBhcGk1LmF1dG9mYXJtZXIubmV0MIIBIjANBgkqhkiG9w0B\
                           AQEFAAOCAQ8AMIIBCgKCAQEAzfma8uGKiAfZFI3/iZR4ih5KGDMkwklLMJy9hmwx\
                           7ahAcn8G1QlJ1U4pYNCnC/Qp20YE0ZCm1ieVcKW+2lp2Xu1kFvuM8L+SBS8qzWLW\
                           Ih0eQh271qkiGSvDSeMkynhqg0VjQJPtRT+fVSnT1K7aGgD1SNQgQRI0LBj3YYBN\
                           6pbqhChKVIahot4d8NfpzITWt92bPFGkZYo1EmLc401Qrzpg+Mko5Mz4LPTqT4wt\
                           NUY2BU22I6jyfWoPZuZo3nJuhRNBbXfx7oDingzKOnIdOkFaMd5XuSa+LJRHG/x1\
                           M9dQ8CjOdZ8sezs57Gi57QpPzmGxW7JkDn2vPXHnSqsJDQIDAQABo4GFMIGCMAkG\
                           A1UdEwQCMAAwHQYDVR0OBBYEFPjyjVLERrpY+29eLiAv5k/5o01iMB8GA1UdIwQY\
                           MBaAFKRMljQCPs9Gu2XoevZO7VgIap5lMDUGA1UdHwQuMCwwKqAooCaGJGh0dHA6\
                           Ly93d3cueW91cmRvbWFpbi5jb20vY2EvY3JsLnBlbTANBgkqhkiG9w0BAQsFAAOC\
                           AQEAQXsWhfFlWGz6DcYVcu8Bc1FVrXtJ0a6zU9M08SBsM7ZiwOqz7c8XY7eG2ipx\
                           uPJ0oL5QwKxbRCS/m+eA/tvzTeotzwd5B/gd4sYt1AWlcinNwDr0413Op5Ac0a1d\
                           gYgZfx5nD7z+Uklyn+vkVPLA4PbjUGbJ35q1SDHL2KioZPjTEQ6QTtrT+binGPCD\
                           wXyn+NN9ctv86c2Oq1bbZrXkPVzdSTSLlT0wphDBRZ3hYPdyfHdh6JbVFnwtY6TU\
                           U8svoBNEI7pSheciY0ZWhayfiBGKfDO7o1a3PWlWjRJ5ohg8Gixc8/uo3O+fp2SV\
                           P9eVv1MXwMJYNiKD1EZI9EYniQ==\
                           -----END CERTIFICATE-----");
    if (success != true) {
        LOGD <<"append cert error: " << cert.lastErrorText();
        return false;
    }

    // Load the private key.
    CkBinData bd;
    success = bd.LoadFile("/Users/phongdang/Temp/mobileapp@cpp.autofarmer.xyz/mobileapp.key");
    success = privKey.LoadEncryptedPem("-----BEGIN PRIVATE KEY-----\
                                       MIIEvgIBADANBgkqhkiG9w0BAQEFAASCBKgwggSkAgEAAoIBAQDN+Zry4YqIB9kU\
                                       jf+JlHiKHkoYMyTCSUswnL2GbDHtqEByfwbVCUnVTilg0KcL9CnbRgTRkKbWJ5Vw\
                                       pb7aWnZe7WQW+4zwv5IFLyrNYtYiHR5CHbvWqSIZK8NJ4yTKeGqDRWNAk+1FP59V\
                                       KdPUrtoaAPVI1CBBEjQsGPdhgE3qluqEKEpUhqGi3h3w1+nMhNa33Zs8UaRlijUS\
                                       YtzjTVCvOmD4ySjkzPgs9OpPjC01RjYFTbYjqPJ9ag9m5mjecm6FE0Ftd/HugOKe\
                                       DMo6ch06QVox3le5Jr4slEcb/HUz11DwKM51nyx7OznsaLntCk/OYbFbsmQOfa89\
                                       cedKqwkNAgMBAAECggEAD4drDDa+6ASXdDpEcs3zzI3+DhcFBXTbK14V1+WeWgme\
                                       WkODc1pQ67kJ25e/kGInKbX8tQQP4AN5+9UzL2k0lXGWYzkx5hC7ZJKqynNSK55A\
                                       YsG1ILj9riIjhhWO94jelukLU5oTgG4MiDIwG0/Xd7BszcHYcK97qXt0YzB2L2Jw\
                                       s+mJMhmq/aV3h0EKFFN1tzcQL5GvioBEBRGvzMHNzKmLHDBtjF6zB+qDGMCd6qaW\
                                       piWRID36MLLQ4JDE5aES3Wlc0jmIa0ZqigpB6QM8UBfqJpV6O3F5ABU1bS/RJ1iL\
                                       0EI7u60xub75auPRtBwLsIUsSEEzWZIzP63GqB03wQKBgQD2XbjiTQ1IjUU1YA7z\
                                       dyoFUpnIZ9IjPOR60ctdRJE9pyMLbXYb3cFsdFaY++FC77NaVeCb9JILAkfcgx57\
                                       kQZWW+Dw/wNsAWoxGL0X5xXvDSqLBUBQjvR48u8ItSeXM9WCCR34FPlwdCgP1A8s\
                                       QAM7LN8IrekbtltSxYh0LuQSUQKBgQDWB4sRa1+Xz8ieIIg7iNPLnAp/2OifxQYs\
                                       YBu6WeXbdzVyx5rgA4+XmxwQL6xvTzx5Ghg4m2v0wvGfJ+EimH+aBuK4SGhDJrYg\
                                       bN3r38LnzJrCnC+7KWH3OGQkbHdhv3c0W/pp46FcitjDuQ5yr5RULJRI9gnBpYMM\
                                       8bgbmtM//QKBgB+jKXrmKi6G9bxE+aaKRvsoAFeb/YBI8Y5UIql3hK9GJ1nwVJp/\
                                       f7dNuVEsB2FxJrcTECT240pGoLPQorl7hjTQ17IbDXVxORHU+3N2WXq5Vh1EL14o\
                                       /XwKtmeH2+2u2lw4j4CsMNwgDoT51nj4P3H58SpMKwNEB7Y5Z6yD2QYBAoGBAKjJ\
                                       DBfxqFJNb3WcTDM/BV+lr/YAtfsBYovuQw+jw4xep0zcMrwEsuGpVelB32dsglEy\
                                       jfVeRDWi4u9TgM1KnB543aTcnTSPu8M4d46DSO6KQWXFzDJ6QSK4WukKjN8OIlCt\
                                       VH7bH66eZLF9J/KzmnMDMPGU7j7DauTzXvCOGZh1AoGBAL3dQV3Iu+j2eDWSeYBg\
                                       PnytU501OlVXptVmwF68TuGB83lpfV5ZPcAjFI7g1Gpuo3Y6L1PgYU/hN7HUdXWg\
                                       +DAqNa/Tm2vA5rs484+aNpXZo7rjf7BRZfOagEGrprCwHRDaZB73OnZMBrMy6YSg\
                                       zTmmDl4Q3CimkfVVa6Kyv9Re\
                                       -----END PRIVATE KEY-----","api5");
    if (success != true) {
        LOGD <<"load key error: " << privKey.lastErrorText();
        return false;
    };

    // Associate the private key with the cert.
    success = cert.SetPrivateKey(privKey);
    if (success != true) {
        LOGD <<  "SetPrivateKey error: " << cert.lastErrorText();
        return false;
    }

    success = http.SetSslClientCert(cert);
    if (success != true) {
        LOGD << "SetSslClientCert error: " << http.lastErrorText();
        return false;
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

#if 0
    QFile bkFile("../../../../PDT/DataBackup/2021-5-15-18-16.json");
    if (bkFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        defArrStr = bkFile.readAll();
        LOGD << "defArrStr: " << defArrStr;
    }
#endif

    QString bkFileName = "../../../../PDT/DataBackup/V2_" + \
            QString::number(QDate::currentDate().year()) + "-" + \
            QString::number(QDate::currentDate().month() + 1) + "-" + \
            QString::number(QDate::currentDate().day()) + "-" + \
            QString::number(QTime::currentTime().hour()) + "-" + \
            QString::number(QTime::currentTime().minute()) + ".json";

    QFile jsonFile(bkFileName);
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(defArrStr.toUtf8());
    jsonFile.close();

    QJsonObject bodyData, response;
    bodyData["action"] = "SaveJasmine";
    bodyData["jasmine_data"] = QString(defArrStr.toUtf8().toBase64());

    QMap<QString,QString> header;
    header.insert("save-jasmine-secret-key","0b21335f-f715-40e1-b312-b099cd87ec4e");
    sendRequest(bodyData, response, "config",header);
    LOGD << "response: " << response;
}

bool WebAPI::upsertDevice()
{
    QJsonObject bodyData, response;
    bodyData["action"] = "Upsert";

    if (sendRequest(bodyData, response, "config"))
    {
        QJsonObject server_data = response["data"].toObject();
        LOGD << "server_data: " << server_data;
        if (server_data["code"].toInt() == 200)
        {
            return true;
        }
    }
    return false;
}



