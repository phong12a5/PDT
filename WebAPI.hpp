#ifndef WEBAPI_H
#define WEBAPI_H

#include <QObject>
#include <iostream>
#include <QMap>
#include <CkJsonObject.h>

#define KEY_PAIR        std::pair<std::string,std::string>
#define KEY_PREFIX      "Congaubeo@123"
#define FACEBOOK_APP    "facebook"
#define INSTAGRAM_APP   "instagram"
#define COMMON_APP      "common"
#define APPNAME         FACEBOOK_APP

class WebAPI : public QObject
{
    Q_OBJECT

private:
    explicit WebAPI(QObject *parent = nullptr);

    QString md5(QString input);
    std::string getCurrentTime();
    std::pair<std::string, std::string> getDynamicKey();
    std::string getEncodedString(std::string input, std::string key);
    std::string encrypt(const char *input, const char *key, const char *iv) ;
    std::string decrypt(const char *input, const char *key, const char *iv);
    std::string encryptTimestamp(const std::string &timestamp, const std::string &token);
    std::string decryptTimestamp(const std::string &timestamp, const std::string &token);
    const char * getIv();
    bool sendRequest(QJsonObject &bodyData, QJsonObject &response, const char *api, QMap<QString, QString> headers);
public:
    static WebAPI *instance();

private:
    static WebAPI* s_instance;

public:
    void getJasmineLog(QList<QJsonObject> &dataContainer);
    void getJamineDefinations(QString& definations);
    void saveJamineDefinations(QJsonArray& defArr);

    signals:
};

#endif // WEBAPI_H
