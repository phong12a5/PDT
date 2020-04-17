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

void WebAPI::getJasmineLog(QList<QJsonObject> &dataContainer)
{
    LOGD << "";
    QString url = "https://log.autofarmer.xyz/api/Jasmine";
    QUrl serviceUrl = QUrl(url);
    QJsonObject json;

    json.insert("action", "GetJasmine");
    json.insert("token", "1bba41b4a6171a82b23b2cfb85ebefea");

    QByteArray jsonData = QJsonDocument(json).toJson();

    CkHttpRequest req;
    CkHttp http;
    http.SetRequestHeader("Content-Type","application/xml; charset=utf-8");

//    LOGD << "url:  " << url;
//    LOGD << "jsonData.data(): " << jsonData.data();
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
                CkJsonArray loggArr;
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
}



