#ifndef WEBAPI_H
#define WEBAPI_H

#include <QObject>

class WebAPI : public QObject
{
    Q_OBJECT

private:
    explicit WebAPI(QObject *parent = nullptr);

public:
    static WebAPI *instance();

private:
    static WebAPI* s_instance;

public:
    void getJasmineLog(QList<QJsonObject> &dataContainer);

public slots:

signals:
};

#endif // WEBAPI_H
