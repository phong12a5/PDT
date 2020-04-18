#ifndef WEBAPI_H
#define WEBAPI_H

#include <QObject>
#include <iostream>
#include <QMap>

#define KEY_PAIR        std::pair<std::string,std::string>
#define KEY_PREFIX      "Congaubeo@123"

class WebAPI : public QObject
{
    Q_OBJECT

private:
    explicit WebAPI(QObject *parent = nullptr);

    std::string getCurrentTime();
    std::pair<std::string, std::string> getDynamicKey();
    std::string getEncodedString(std::string input, std::string key);
    std::string encrypt(const char *input, const char *key, const char *iv) ;
    std::string decrypt(const char *input, const char *key, const char *iv);
    const char * getIv();
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
