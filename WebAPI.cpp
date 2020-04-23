#include "WebAPI.hpp"
#include <QEventLoop>
#include <CkJsonObject.h>
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

#define MODEL AppModel::instance()

WebAPI* WebAPI::s_instance = nullptr;

WebAPI::WebAPI(QObject *parent) : QObject(parent)
{
    // Do nothing
}

WebAPI *WebAPI::instance()
{
    if(s_instance == nullptr){
        s_instance = new WebAPI();
    }
    return s_instance;
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

const char * WebAPI::getIv() {
    return "Congaubeo@123560";
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
    CkHttp http;
    http.SetRequestHeader("Content-Type","application/xml; charset=utf-8");

    CkHttpResponse *resp = nullptr;
    resp = http.PostJson2(url.toLocal8Bit().data(), "application/json", jsonData.data());
    if (http.get_LastMethodSuccess() != true) {
        LOGD << "Http error: " + QString(http.lastErrorText());
    } else {
        if (resp->bodyStr()) {
            CkJsonObject jsonResponse;
            bool loadJson = jsonResponse.Load(resp->bodyStr());
            if (loadJson) {
                const char * data = jsonResponse.stringOf("data");
                QJsonDocument doc = QJsonDocument::fromJson(data);
                if(doc.isArray()) {
                    QJsonArray arr = doc.array();
                    for (int j = 0; j < arr.size(); j++) {
                        QJsonObject obj = arr.at(j).toObject();
                        QJsonObject logElement = QJsonDocument::fromJson(obj.value("info").toString().toLocal8Bit().data()).object();
                        dataContainer.append(logElement);
                    }
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
    QString url = "https://api.autofarmer.net/api3/config?token=496UTSHK4XMCNV1WEYP41K";
    QJsonObject json;

    KEY_PAIR keyPair = getDynamicKey();
    json.insert("client_timestamp", keyPair.second.data());
    json.insert("action", this->getEncodedString("GetJasmine",keyPair.first).data());
    json.insert("info", this->getEncodedString("MyComputer",keyPair.first).data());

    QByteArray jsonData = QJsonDocument(json).toJson();

    CkHttpRequest req;
    CkHttp http;
    http.SetRequestHeader("Content-Type","application/xml; charset=utf-8");

    CkHttpResponse *resp = nullptr;
    resp = http.PostJson2(url.toLocal8Bit().data(), "application/json", jsonData.data());
    if (http.get_LastMethodSuccess() != true) {
        LOGD << "Http error: " + QString(http.lastErrorText());
    } else {
        if (resp->bodyStr()) {
            CkJsonObject jsonResponse;
            bool loadJson = jsonResponse.Load(resp->bodyStr());
            if (loadJson) {
                jsonResponse.put_EmitCompact(false);
                if (jsonResponse.HasMember("data")) {
                    if(jsonResponse.HasMember("server_timestamp")){
                        std::string serverTimeStamp = std::string(jsonResponse.stringOf("server_timestamp"));
                        std::string key = std::string(KEY_PREFIX) + serverTimeStamp + serverTimeStamp;
                        key = key.substr(0,32);
                        std::string result = this->decrypt(jsonResponse.stringOf("data"),key.data(), this->getIv());

                        CkString ckstr;
                        ckstr.setStringUtf8(result.data());
                        ckstr.base64Decode("utf-8");

                        CkJsonObject tempJson;
                        tempJson.put_Utf8(true);
                        tempJson.Load(ckstr.getUtf8());
                        if(tempJson.HasMember("success") && tempJson.BoolOf("success") == true && tempJson.HasMember("data")){
                            definations = tempJson.stringOf("data");
                        }
                    }else {
                        LOGD << "Could not get server_timestamp";
                    }
                } else {
                    LOGD << "Data field is not existed!";
                }
            }
        } else {
            LOGD << "resp->bodyStr() is NULL";
        }
    }
}

void WebAPI::saveJamineDefinations(QJsonArray &defArr)
{
    QString defArrStr = QJsonDocument(defArr).toJson();
    LOGD << "";
    QString url = "https://api.autofarmer.net/api3/config?token=496UTSHK4XMCNV1WEYP41K";
    QJsonObject json;

    KEY_PAIR keyPair = getDynamicKey();
    json.insert("client_timestamp", keyPair.second.data());
    json.insert("action", this->getEncodedString("SaveJasmine",keyPair.first).data());
    json.insert("data", this->getEncodedString(std::string(defArrStr.toUtf8().data()),keyPair.first).data());
    json.insert("info", this->getEncodedString("MyComputer",keyPair.first).data());

    QByteArray jsonData = QJsonDocument(json).toJson();

    CkHttpRequest req;
    CkHttp http;
    http.SetRequestHeader("Content-Type","application/xml; charset=utf-8");

    CkHttpResponse *resp = nullptr;
    resp = http.PostJson2(url.toLocal8Bit().data(), "application/json", jsonData.data());
    if (http.get_LastMethodSuccess() != true) {
        LOGD << "Http error: " + QString(http.lastErrorText());
    } else {
        if (resp->bodyStr()) {

            CkJsonObject jsonResponse;
            bool loadJson = jsonResponse.Load(resp->bodyStr());
            if (loadJson) {
                jsonResponse.put_EmitCompact(false);
                if (jsonResponse.HasMember("data")) {
                    if(jsonResponse.HasMember("server_timestamp")){
                        std::string serverTimeStamp = std::string(jsonResponse.stringOf("server_timestamp"));
                        std::string key = std::string(KEY_PREFIX) + serverTimeStamp + serverTimeStamp;
                        key = key.substr(0,32);
                        std::string result = this->decrypt(jsonResponse.stringOf("data"),key.data(), this->getIv());
                        LOGD << "result: " << QByteArray::fromBase64(result.data());
                    }else {
                        LOGD << "Could not get server_timestamp";
                    }
                } else {
                    LOGD << "Data field is not existed!";
                }
            } else {
                LOGD << "Load responsed failed";
            }
        } else {
            LOGD << "resp->bodyStr() is NULL";
        }
    }
}



