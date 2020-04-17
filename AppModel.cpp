#include "AppModel.h"
#include "WebAPI.hpp"
#include <QJsonDocument>
#include <QString>

AppModel* AppModel::m_instance = nullptr;

AppModel::AppModel(QObject *parent) : QObject(parent)
{
    getLogFromServer();
}

AppModel *AppModel::instance()
{
    if(m_instance == nullptr){
        m_instance = new AppModel();
    }
    return m_instance;
}

QList<QObject *> AppModel::listLogRecord()
{
    return m_listLogRecord;
}

void AppModel::getLogFromServer()
{
    QList<QJsonObject> listRecord;
    WebAPI::instance()->getJasmineLog(listRecord);
    LOGD << listRecord.length();
    if(!listRecord.isEmpty()) {
        qDeleteAll(m_listLogRecord);
        foreach(QJsonObject logObj , listRecord) {
            m_listLogRecord.append(new LogElement(logObj));
            emit listLogRecordChanged();
        }
    }
}




