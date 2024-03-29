#include "AppModel.h"
#include "WebAPI.hpp"
#include <QJsonDocument>
#include <QString>
#include <QMessageBox>
#include <QFile>
#include <QDateTime>
#include <QDir>
#include <QAbstractButton>

#define DEVICE_ID       "764ac7fc42f75e09"

AppModel* AppModel::m_instance = nullptr;

AppModel::AppModel(QObject *parent) : QObject(parent)
{
    settings = new QSettings("PDT","PDT");
    QDir().mkdir(QDir::currentPath() + "/images");
    LOGD << "Created";
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

QStringList AppModel::listPageID() const
{
    return  m_definationMap.keys();
}

QStringList AppModel::listLanguage() const
{
    return LANG_MAP.keys();
}

QString AppModel::androidID() const
{
    QString android_id =  settings->value("android_id").toString();
    if(android_id.isNull() || android_id.isEmpty()) {
        return "0000000000";
    }
    return settings->value("android_id").toString();
}

void AppModel::setAndroidID(QString data)
{
    if(data != settings->value("android_id").toString()) {
        settings->setValue("android_id", data);
        emit androidIDChanged();
    }
}

void AppModel::insertPageDefinations(QJsonObject pageObj)
{
    if(!pageObj.isEmpty()) {
        m_definationMap.insert(pageObj.value("screen").toString(),pageObj);
        emit listPageIDChanged();
    }
}

QJsonObject AppModel::getPageDefinations(QString pageID)
{
    return m_definationMap.value(pageID);
}

void AppModel::getLogFromServer()
{
    LOGD << "";
    qDeleteAll(m_listLogRecord);
    m_listLogRecord.clear();
    emit listLogRecordChanged();

    QList<QJsonObject> listRecord;
    WebAPI::instance()->getJasmineLog(listRecord, androidID());
    LOGD << "Record log count: " << listRecord.count();
    if(!listRecord.isEmpty()) {
        foreach(QJsonObject logObj , listRecord) {
            m_listLogRecord.append(new LogElement(m_listLogRecord.length(),logObj));
        }
        emit listLogRecordChanged();
    }
}

void AppModel::saveResult()
{
    LOGD << "";
    QJsonArray defArr;
    foreach (QString pageID, m_definationMap.keys()) {
        defArr.append(m_definationMap.value(pageID));
    }

    if(!defArr.isEmpty()) {
        QString code;
        WebAPI::instance()->getAuthCode(code);
        WebAPI::instance()->saveDefinations(defArr, code);
    }
}

bool AppModel::publish()
{
    QString code;
    WebAPI::instance()->getAuthCode(code);
    return WebAPI::instance()->approveDefinition(code);
}

void AppModel::getScreenDefinitions()
{
    QString defStr;
    WebAPI::instance()->getScreenDefinitions(defStr);
    QJsonDocument defDoc = QJsonDocument::fromJson(defStr.toUtf8());
    if(defDoc.isArray()) {
        QJsonArray defArr = defDoc.array();
        if(defArr.size() > 0) {
            m_definationMap.clear();
            for (int i = 0; i < defArr.size(); i++) {
                QJsonObject pageObj = defArr.at(i).toObject();
                if(!pageObj.isEmpty()) {
                    LOGD << pageObj;
                    insertPageDefinations(pageObj);
                }
            }
            LOGD << "Get json successfully with " << m_definationMap.size() << "records";
            return;
        }
    }
    LOGD << "Get json failed";
}

void AppModel::getLocalScreenDefinitions(QString path)
{
    if(path.startsWith("file://")) path = path.replace("file://", "");
    LOGD << path;
    QFile jsonFile(path);
    if (jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QJsonDocument defDoc = QJsonDocument::fromJson(jsonFile.readAll());
        if(defDoc.isArray()) {
            QJsonArray defArr = defDoc.array();
            if(defArr.size() > 0) {
                m_definationMap.clear();
                for (int i = 0; i < defArr.size(); i++) {
                    QJsonObject pageObj = defArr.at(i).toObject();
                    if(!pageObj.isEmpty()) {
                        insertPageDefinations(pageObj);
                    }
                }
                LOGD << "Get json successfully with " << m_definationMap.size() << "records";
                return;
            }
        }
    }
    LOGD << "Get json failed";
}

void AppModel::updateJamineDefinations(QString appName, QString pageID, QString language, QList<QObject *> nodeList)
{
    LOGD << "appName: " << appName << " -- pageID: " << pageID << " -- langCode: " << language << " -- nodeList: " << nodeList.length();
    if(pageID == "SCREEN_UNKNOWN") {
        LOGD << "Reject SCREEN_UNKNOWN";
        QMessageBox Msgbox;
        Msgbox.setText("Reject SCREEN_UNKNOWN!");
        Msgbox.exec();
        return;
    }
    if(LANG_MAP.contains(language)){
        QJsonObject pageObj = this->getPageDefinations(pageID);
        QJsonObject definationsField = pageObj.value("definitons").toObject();
        QJsonArray arrEdidenceByLange = definationsField[language].toArray();
        QJsonArray newEvidence;
        for (int i = 0; i < nodeList.length(); i++) {
            QJsonObject evidenceItem;
            evidenceItem.insert("text",static_cast<ASBLTNode*>(nodeList.at(i))->text());
            evidenceItem.insert("contentDescription",static_cast<ASBLTNode*>(nodeList.at(i))->contentDescription());
            evidenceItem.insert("className",static_cast<ASBLTNode*>(nodeList.at(i))->className());
            evidenceItem.insert("clickable",static_cast<ASBLTNode*>(nodeList.at(i))->clickable());
            evidenceItem.insert("checked",static_cast<ASBLTNode*>(nodeList.at(i))->checked());
            evidenceItem.insert("selected",static_cast<ASBLTNode*>(nodeList.at(i))->selected());
            newEvidence.append(evidenceItem);
        }
        if(!arrEdidenceByLange.contains(newEvidence))
            arrEdidenceByLange.append(newEvidence);
        definationsField.insert(language,arrEdidenceByLange);
        pageObj.insert("definitons",definationsField);
        pageObj.insert("page",pageID);
        pageObj.insert("appname",appName);
        LOGD << "pageObj: " << pageObj;
        insertPageDefinations(pageObj);
    }
}

void AppModel::updateJamineKeyword(QString appName, QString pageID, QString language, QList<QObject *> nodeList)
{
    LOGD << "appName: " << appName << " -- pageID: " << pageID << " -- langCode: " << language << " -- nodeList: " << nodeList.length();
    if(pageID == "SCREEN_UNKNOWN") {
        LOGD << "Reject SCREEN_UNKNOWN";
        QMessageBox Msgbox;
        Msgbox.setText("Reject SCREEN_UNKNOWN!");
        Msgbox.exec();
        return;
        return;
    }
    if(LANG_MAP.contains(language)){
        QJsonObject pageObj = this->getPageDefinations(pageID);
        QJsonObject keywordsField = pageObj.value("keywords").toObject();
        QJsonArray arrKeywordByLang = keywordsField[language].toArray();
        for (int i = 0; i < nodeList.length(); i++) {
            QJsonObject keywordItem;
            keywordItem.insert("text",static_cast<ASBLTNode*>(nodeList.at(i))->text());
            keywordItem.insert("contentDescription",static_cast<ASBLTNode*>(nodeList.at(i))->contentDescription());
            keywordItem.insert("className",static_cast<ASBLTNode*>(nodeList.at(i))->className());
            keywordItem.insert("clickable",static_cast<ASBLTNode*>(nodeList.at(i))->clickable());
            keywordItem.insert("checked",static_cast<ASBLTNode*>(nodeList.at(i))->checked());
            keywordItem.insert("selected",static_cast<ASBLTNode*>(nodeList.at(i))->selected());
            keywordItem.insert("keyword",static_cast<ASBLTNode*>(nodeList.at(i))->keyword());
            if(!arrKeywordByLang.contains(keywordItem))
                arrKeywordByLang.append(keywordItem);
        }
        keywordsField.insert(language,arrKeywordByLang);
        pageObj.insert("keywords",keywordsField);
        pageObj.insert("page",pageID);
        pageObj.insert("appname",appName);
        LOGD << "pageObj: " << pageObj;
        insertPageDefinations(pageObj);
    }
}

QStringList AppModel::getListIDComponent(QString pageID, QString language)
{
    QStringList result;
    QJsonObject pageObj = this->getPageDefinations(pageID);
    QJsonObject keywordsField = pageObj.value("keywords").toObject();
    QJsonArray arrKeywordByLang = keywordsField[language].toArray();
    for(int i = 0; i < arrKeywordByLang.size(); i++){
        QJsonObject item = arrKeywordByLang.at(i).toObject();
        if(item.contains("keyword")){
            if(!result.contains(item.value("keyword").toString()))
                result.append(item.value("keyword").toString());
        }
    }
    return result;
}

QString AppModel::getAppNameByScreenID(QString screenID) {
    QJsonObject pageObj = this->getPageDefinations(screenID);
    return pageObj.value("appname").toString();
}




