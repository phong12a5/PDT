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
#include <CkTask.h>
#include <QMessageBox>


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
    QString url = QString("https://api81.autofarmer.net/cgi-bin/autofarmer_1_1.cgi?api=%1&token=%2").arg(api).arg(token);
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
    success = cert.LoadPem("-----BEGIN CERTIFICATE-----\n"
                           "MIIEHDCCAwSgAwIBAgIDEAACMA0GCSqGSIb3DQEBCwUAMIGMMQswCQYDVQQGEwJV\n"
                           "UzETMBEGA1UECAwKU29tZS1TdGF0ZTEhMB8GA1UECgwYYXBpODEuYXV0b2Zhcm1l\n"
                           "ci5uZXQgTHRkMR0wGwYDVQQDDBRhcGk4MS5hdXRvZmFybWVyLm5ldDEmMCQGCSqG\n"
                           "SIb3DQEJARYXY2FAYXBpODEuYXV0b2Zhcm1lci5uZXQwHhcNMjExMDA0MDI0NDMx\n"
                           "WhcNMzExMDAyMDI0NDMxWjCBizELMAkGA1UEBhMCVVMxHDAaBgNVBAgTE1N0YXRl\n"
                           "IG9yIFByb3ZpZGVuY2UxEDAOBgNVBAoTB0NvbXBhbnkxHTAbBgNVBAMTFGFwaTgx\n"
                           "LmF1dG9mYXJtZXIubmV0MS0wKwYJKoZIhvcNAQkBFh5tb2JpbGVhcHBAYXBpODEu\n"
                           "YXV0b2Zhcm1lci5uZXQwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCs\n"
                           "sTW157pb0gGIEk85ctrp7Ou0YWnaBJEFsB5GKzR9R6WteJukx4bi5dZG9XbnDIT2\n"
                           "k1wycZjEoF3QlTJNLy7wRmUCGpexhxboG7vYOLY2fKRGqZt1xmz3gW92MyOGP6tF\n"
                           "7HdtshHEACPNS0nJUf/NNdNz0DKdhC6sllhw29V1f3kgozYzpw4Ml2Jgx95/wOej\n"
                           "ZWnB957Sl+dbi4j68RnrNqujxs2vCpAfiX8C99OXtA8xXn2Edrceh6WzG47I1Fze\n"
                           "nYCzwBQr4Uh/b7/0ONAiwi09+dip0him2UVkFyOL5CIVbz3B5z69r01fEGVqiJxk\n"
                           "Gy2Sdl+IT2ZBePadFZSjAgMBAAGjgYUwgYIwCQYDVR0TBAIwADAdBgNVHQ4EFgQU\n"
                           "80m4EkOkNdZB3mBL2UjnwqFYhXQwHwYDVR0jBBgwFoAU9IzMtFOJVdqPvm1Hfv4M\n"
                           "C6m8WEQwNQYDVR0fBC4wLDAqoCigJoYkaHR0cDovL3d3dy55b3VyZG9tYWluLmNv\n"
                           "bS9jYS9jcmwucGVtMA0GCSqGSIb3DQEBCwUAA4IBAQBB2gAlD2lHGvkSet1uTmLq\n"
                           "vDtosXEbXoCguHAY+poVumN9e0p4M4ue6y27QyT7pyY/YGbsFKYpYKHUcqqtNiNW\n"
                           "jErRc0ifLJ2OILKggWILp+QwyotJLCHVrXmrbYIMzgM7PD07lzgx+1IYrp9UycnA\n"
                           "2TIjclPaLmFtIy6eH9xvicmqRlcrm68gu0fC/cL7aMP1WW3rBF9Oz+ZqPU+7FcyU\n"
                           "XVvAiM+frVcgnm4M0wnc1QLupkz/myWC48+gXZH6QRSbXEKVZd1TqUxpD2+XgIPy\n"
                           "EgwEqV8GAw0gyHgol8RnE/r3mIC9vM0pjxZgaUWOJJIT/yWnJ3e8ZJr/1YoOHP4u\n"
                           "-----END CERTIFICATE-----");
    if (success != true) {
        LOGD <<"append cert error: " << cert.lastErrorText();
        return false;
    }

    // Load the private key.
    CkBinData bd;
    success = bd.LoadFile("/Users/phongdang/Temp/mobileapp@cpp.autofarmer.xyz/mobileapp.key");
    success = privKey.LoadEncryptedPem("-----BEGIN PRIVATE KEY-----\n"
                                       "MIIEvwIBADANBgkqhkiG9w0BAQEFAASCBKkwggSlAgEAAoIBAQCssTW157pb0gGI\n"
                                       "Ek85ctrp7Ou0YWnaBJEFsB5GKzR9R6WteJukx4bi5dZG9XbnDIT2k1wycZjEoF3Q\n"
                                       "lTJNLy7wRmUCGpexhxboG7vYOLY2fKRGqZt1xmz3gW92MyOGP6tF7HdtshHEACPN\n"
                                       "S0nJUf/NNdNz0DKdhC6sllhw29V1f3kgozYzpw4Ml2Jgx95/wOejZWnB957Sl+db\n"
                                       "i4j68RnrNqujxs2vCpAfiX8C99OXtA8xXn2Edrceh6WzG47I1FzenYCzwBQr4Uh/\n"
                                       "b7/0ONAiwi09+dip0him2UVkFyOL5CIVbz3B5z69r01fEGVqiJxkGy2Sdl+IT2ZB\n"
                                       "ePadFZSjAgMBAAECggEAZ9QH8f2IG2qxRwmTHnxCyICM2p/zD4TNWLkiCpgxb91i\n"
                                       "7GBmW/Um0UbUxUcSHSp2yvWgaifIbPfqT91UJ/nlY8s/MbuhVrhc+mKqVv8J9sqL\n"
                                       "znxtHquVml31EQEAK9gd9uWMjKSSb+CRpf3NOECX5t6k6q3TsMbndRbTx880kPZ9\n"
                                       "ZMyjzqhFFiKQLW73/P5qz4MlHoyNTGuj9EEqYmhvZ+BJ6RMxoBgAxbo/MeYVRm/m\n"
                                       "fb7GWvtdTCabaTiNhtoB3emSiq5RSZCSkF3oXl2IFF99jLbWh2Q5OYw71vPAmwjk\n"
                                       "5zlcptVbBeNI+7CNXCsgiHwL04XDXrVeLWdnb6Nw2QKBgQDbLdvIwzveOETFnbBx\n"
                                       "XtKdTpEIanD2brvgmnUdeeA00VhKl16+2nE0xVq6L5qJw5+3aNCOT7dcvshIaRsn\n"
                                       "6sLDjCROp29otPG5t5oloR7S9l+fW32NjA/AbWoU43DPcPG4F3O+RyByHT+tW0wg\n"
                                       "gop14oqL1WRVWlIKuqRAFNcafQKBgQDJtBvqpzutGe1PQoCpUsKKgkUKQIW6zXsn\n"
                                       "d5fV2xUofE5jYOYbh7kMx5q/uyenoNY01QA6d+824LMveTwY/FWrYl5fgXgm7V6x\n"
                                       "q3Ixx7dbCSKeOtDWPaXboIMh9GICYZx3T2TpfUV3ErPjuEMOoeMoTuyA3eBWsqco\n"
                                       "ENDzyrV1nwKBgQCZhBpQGScCs+i/fX6LOb5NPi1pdpxejxr661Sia631cLflrvZG\n"
                                       "uVvXeW/dvuAAJEvnO/vv4bfttxczWKMTp2P5cVww1ye6cBprWUUXnC2p17UMOhnL\n"
                                       "ndGel0RZEyD9uv8jURHZsZnxM7lZI/xDPQvcG+usm69l9RhHuYi39aDgRQKBgQCz\n"
                                       "XZXhsntP8JlmfUX6zNyw3S1V85C4UFfu/duo0hzblscCer3Fx4jYg3vqehzGZTF3\n"
                                       "Y97DH7o6+9B8K/w0X9gzAtPXbEOTokwuBL8U43v62YHOYZEqo0Glr/RMsoyhf3nr\n"
                                       "Y0/ijoLCY4BSxZ3kGjPtuVl5M1V244HgECwwT5fUEwKBgQDO3v/bCmf5D9IABsFA\n"
                                       "q9wOixh9rh1i9wzl04iXAdufkYnH1owefmOyjU7XMbbLQpZH0VSRq+W8yxOcRXR0\n"
                                       "ndct4OmPtLZJW628u7eZiEwtfQT0vAChvqsSulDd9pZz+vD6U1k2Wa6LgvvFuhOk\n"
                                       "7igmuY9QNP4zIKztizrPuiSaqQ==\n"
                                       "-----END PRIVATE KEY-----","7mnBBM9aX9nkD8Sq");
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


void WebAPI::getJasmineLog(QList<QJsonObject> &dataContainer, QString androidID)
{
    LOGD << "";
    QString url = "https://log-internal-api.congaubeo.us/v1/log-screen/search";
    QJsonObject json;

    json.insert("created_source", "android_phong");
    json.insert("page", 1);
    json.insert("limit", 20);
    json.insert("android_id", androidID);

    QByteArray jsonData = QJsonDocument(json).toJson(QJsonDocument::Compact);

    CkHttpRequest req;
    CkHttp http ;
    http.put_Utf8(true);
    http.SetRequestHeader("Content-Type","application/json");

    CkCert cert;
    CkPrivateKey privKey;
    bool importCert = false;

    // Load any type of certificate (.cer, .p7b, .pem, etc.) by calling LoadFromFile.
    importCert = cert.LoadPem("-----BEGIN CERTIFICATE-----\
                              MIIERjCCAy6gAwIBAgIDEAACMA0GCSqGSIb3DQEBCwUAMIGnMQswCQYDVQQGEwJV\
                              UzETMBEGA1UECAwKU29tZS1TdGF0ZTEqMCgGA1UECgwhbG9nLWludGVybmFsLWFw\
                              aS5jb25nYXViZW8udXMgTHRkMSYwJAYDVQQDDB1sb2ctaW50ZXJuYWwtYXBpLmNv\
                              bmdhdWJlby51czEvMC0GCSqGSIb3DQEJARYgY2FAbG9nLWludGVybmFsLWFwaS5j\
                              b25nYXViZW8udXMwHhcNMjEwNjA3MTYxNjQ3WhcNMzEwNjA1MTYxNjQ3WjCBmjEL\
                              MAkGA1UEBhMCVVMxHDAaBgNVBAgTE1N0YXRlIG9yIFByb3ZpZGVuY2UxEDAOBgNV\
                              BAoTB0NvbXBhbnkxJjAkBgNVBAMTHWxvZy1pbnRlcm5hbC1hcGkuY29uZ2F1YmVv\
                              LnVzMTMwMQYJKoZIhvcNAQkBFiRjbGllbnRAbG9nLWludGVybmFsLWFwaS5jb25n\
                              YXViZW8udXMwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDQeElhMDRB\
                              MXaJztSmKvtS7/yKAZmY9oD/3qp2mYxTfWhvrURDCZqGjUCkvV5H/7iTZqEf8DPG\
                              1C0BXTJkIeeHI1YdS7Dli348ZReSToPb8qLZIXAjWYerk8cKNHC01YyTqjxUPt2Z\
                              2OrEglw8oB+kfkViZ/lU76sA1Bv2bzqBqdm80z30ZHkCXV3OOm6H+KYBlx5qOlZt\
                              Dx4puxufNh2yd5K4hrQ1CjnUEmKYnAjYY/dfKLuw9xVZrFBgfRLNRZZzsXHQ8efL\
                              KgaEaMjIL0/uK6LpxVAo9ESsMBbGEIdMOeyk/hSdOjCEOSLphulfJmUFDXWh7UVU\
                              ztR6yFZ+jjtDAgMBAAGjgYUwgYIwCQYDVR0TBAIwADAdBgNVHQ4EFgQU1ORP7o+0\
                              ASI6o3T9AT8/6zAhIsowHwYDVR0jBBgwFoAUXcrXIQkygn19as2pKfUC2+zk2wsw\
                              NQYDVR0fBC4wLDAqoCigJoYkaHR0cDovL3d3dy55b3VyZG9tYWluLmNvbS9jYS9j\
                              cmwucGVtMA0GCSqGSIb3DQEBCwUAA4IBAQBGkZkknKlTJ2WCRVxXNuy1kdpAnvDa\
                              Hu/LG1NFJZNV+AS3w0e2rOaXPXxHXmkPCmn9noHxqRG1KLurpkGdA73kYfDjjKtL\
                              jJs9p/9Mnmbuk9u11PDVWulm0/bGDVh6tNT4JRjixs1tVpPkrXriPqtSNbhpiasg\
                              cVdn2CD6kXhWAjyVvDHhu/B3gaY3MPb50bWjkR9dXEA5evwe5lMa2TuafwK3PV20\
                              e7qk044G35j+UlaWi5MX19iqJpwqCgVgQGViH5dUAqLvPmY4dm/1nKT1OeXFymlY\
                              Tdc4Rpddrq4ryfn5eiPhmbbII9FzM+abGXCFxwkXhbP2KuTQgP87NvO1\
                              -----END CERTIFICATE-----");
    if (importCert != true) {
        LOGD <<"append cert error: " << cert.lastErrorText();
        return;
    }


    // Load the private key.
    CkBinData bd;
    importCert = bd.LoadFile("/Users/phongdang/Temp/mobileapp@cpp.autofarmer.xyz/mobileapp.key");
    importCert = privKey.LoadEncryptedPem("-----BEGIN PRIVATE KEY-----\
                                          MIIEvgIBADANBgkqhkiG9w0BAQEFAASCBKgwggSkAgEAAoIBAQDQeElhMDRBMXaJ\
                                          ztSmKvtS7/yKAZmY9oD/3qp2mYxTfWhvrURDCZqGjUCkvV5H/7iTZqEf8DPG1C0B\
                                          XTJkIeeHI1YdS7Dli348ZReSToPb8qLZIXAjWYerk8cKNHC01YyTqjxUPt2Z2OrE\
                                          glw8oB+kfkViZ/lU76sA1Bv2bzqBqdm80z30ZHkCXV3OOm6H+KYBlx5qOlZtDx4p\
                                          uxufNh2yd5K4hrQ1CjnUEmKYnAjYY/dfKLuw9xVZrFBgfRLNRZZzsXHQ8efLKgaE\
                                          aMjIL0/uK6LpxVAo9ESsMBbGEIdMOeyk/hSdOjCEOSLphulfJmUFDXWh7UVUztR6\
                                          yFZ+jjtDAgMBAAECggEAdjnxa5O53ssdbbQFtyMjGvsNHnsfz7bkm7d8tvwHsAWs\
                                          J8F8uAQHRY1v/r2CbZSh6b5HXGSOCJGl4GMpQ85SjrpEiSK29McyVTADuS6b6y3k\
                                          mv0yqmmI3o5VT/1Dedqt+cSOqDxq0mhJZB6GDr/EkjYmRVOv/DJbqYGhRhX4eTWD\
                                          D0aMMA1SF7i0oxAR2H3zGc0G6aFpZiW+C7wpXXtLwH9jboejhVZHWIdH2X0i5C/v\
                                          oVYfy6h7omyfqAbq+D/9ZHJ6qabB0mplK27xTg2KyH+syRgi+lUksCW/AdeolXfD\
                                          xqC3qs3VjVLEFsc+SB1Wf34ZY5zNuyVSRdvsevw3KQKBgQDwif0wxnNotochj/FO\
                                          9OXTVXDG6Nx+ujT8FX+XXzM3E33bVXMWh0XCeqZSuFpjwPAaahdtvelgNjimRVD/\
                                          07c26nUo7zWSX4fxWCbGSbpG59ePmpUz5J2LPvJrg6wE6+B3c6uvBI7sqCfCTGEP\
                                          /co4eU2QKCEtCcrJ3qPwXU7NBwKBgQDd3puJQnT9/rcXzSewwJi7aDbXE8PitVu4\
                                          LOO1uIz6xrXboZ/hHiFIK0Mv4OIg9AeYNT5CrPC+ArnYEi+9DEjQwVZ27tOY9hkC\
                                          xtOuqYcfsv1Ja/V80v+pePYDiV+/Me4RZGYLuizCvwULm34TL/oYDkbZuGD1jtxN\
                                          e43z3keM5QKBgQCib3z00D8lioWsy4jYmhcN5Rf4q04jolmflmEIdvieC+KlGIpU\
                                          v1sDn1HscKRR0vwRym0x5drQ5yzQU+UELhP+2MvvrcKOq0ahW7crlqRdt7jhODHj\
                                          zlH5s7N/mXa0CBoYcJuS4FAoTtIyquOtKeTCyF/xprfos0Enm9s3ubs6RwKBgQCW\
                                          p3KruHGiitQemFLsJUtQbgpW7vfjOEyoeerBWSh5nHaeRVg/z2rAC4hauXQy9iE2\
                                          DGlTcwUhsM4q1uaNkwranX2t0qvhwLHo/cN9ZWX4c1yj/2e5M7kghZ9fdWeLd0b1\
                                          jlvweKGuN3EgmZv5QWmr7f3UFuvXsgMLpesU/glNtQKBgH6OUWxC0aFvcKUqbkq2\
                                          XS/d58kW38SdYek61jcNqkYuXmd0ohtjt5gdDjDsOZtSUNejMXG9zFD1N7S4HKE2\
                                          KpG4NHv43rhhCAdiAfF25YAXeAMEMuj2RdSrQn5oIRP/C4vs/M2MKIlN/uXv3ned\
                                          0gpQuAQJk7ISv6YBLcSHZ32C\
                                          -----END PRIVATE KEY-----","client");
    if (importCert != true) {
        LOGD <<"load key error: " << privKey.lastErrorText();
        return;
    };

    // Associate the private key with the cert.
    importCert = cert.SetPrivateKey(privKey);
    if (importCert != true) {
        LOGD <<  "SetPrivateKey error: " << cert.lastErrorText();
        return;
    }

    importCert = http.SetSslClientCert(cert);
    if (importCert != true) {
        LOGD << "SetSslClientCert error: " << http.lastErrorText();
        return;
    }

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
                CkJsonObject* dataObj = jsonResponse.ObjectOf("data");
                if(dataObj != nullptr) {
                    CkJsonArray* dataArr = dataObj->ArrayOf("data");
                    if(dataArr) {
                        LOGD << "dataArr: " << dataArr->get_Size();
                        QList<CkTask*> taskList;
                        QList<CkHttp*> httpList;
                        for(int i = 0; i < dataArr->get_Size(); i++ ){
                            CkJsonObject* recordObj = dataArr->ObjectAt(i);
                            QJsonObject recordQObj;
                            recordQObj["image_url"] = recordObj->stringOf("image_url");
                            recordQObj["screen_id"] = recordObj->stringOf("screen_id");
                            dataContainer.append(recordQObj);
                            CkHttp* http = CkHttp::createNew();
                            CkTask *task =   http->QuickGetStrAsync(recordObj->stringOf("screen_info_url"));
                            task->Run();
                            taskList.append(task);
                            httpList.append(http);
                        }

                        for(int i = 0; i < taskList.size(); i++ ){
                            taskList[i]->Wait(1000);
                        }

                        for(int i = 0; i < taskList.size(); i++ ){
                            if(taskList[i]->get_StatusInt() == 7 && taskList[i]->get_TaskSuccess()) {
                                QJsonObject recordObj = dataContainer[i];
                                recordObj["screen_info"] = taskList[i]->getResultString();
                                dataContainer[i] = recordObj;
                            }
                        }

                        for(int i = 0; i < taskList.size(); i++ ){
                            delete taskList[i];
                            delete httpList[i];
                        }

                        LOGD << "dataContainer: " << dataContainer.size();
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
    QByteArray defArrStr = QJsonDocument(defArr).toJson(QJsonDocument::Compact);
    LOGD << "";
    QString url = "https://api4.autofarmer.xyz/api4/config?token=496UTSHK4XMCNV1WEYP41K";
    QJsonObject json;

#if LOCAL_UPLOAD
    QFile bkFile(QString("/Users/" + qgetenv("USER") + "/autofarmer Dropbox/Auto Farmer/Apps/AutoFarmer.XYZ/Definitions backup/") + LOCAL_FILE);
    if (bkFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        defArrStr = bkFile.readAll();
        QJsonDocument document = QJsonDocument().fromJson(defArrStr);
        QJsonArray arrayDefinition = document.array();
        if(arrayDefinition.isEmpty()) {
            QMessageBox Msgbox;
            Msgbox.setText("Parse error");
            Msgbox.exec();
            return;
        }
        else {
            LOGD << "arrayDefinition: " << arrayDefinition;
        }
    }
#else

    QString bkFileName = "/Users/" + qgetenv("USER") + "/autofarmer Dropbox/Auto Farmer/Apps/AutoFarmer.XYZ/Definitions backup/V2_" + \
            QString::number(QDate::currentDate().year()) + "-" + \
            QString::number(QDate::currentDate().month()) + "-" + \
            QString::number(QDate::currentDate().day()) + "-" + \
            QString::number(QTime::currentTime().hour()) + "-" + \
            QString::number(QTime::currentTime().minute()) + ".json";

    QFile jsonFile(bkFileName);
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(QJsonDocument(defArr).toJson());
    jsonFile.close();
#endif

    QJsonObject bodyData, response;
    bodyData["action"] = "SaveJasmine";
    bodyData["jasmine_data"] = QString(defArrStr.toBase64());

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



