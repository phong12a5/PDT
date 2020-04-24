#include "AppModel.h"
#include "WebAPI.hpp"
#include <QJsonDocument>
#include <QString>
#include <QMessageBox>
#include <QFile>
#include <QDateTime>
#include <QDir>

AppModel* AppModel::m_instance = nullptr;

AppModel::AppModel(QObject *parent) : QObject(parent)
{
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

void AppModel::insertPageDefinations(QJsonObject pageObj)
{
    if(!pageObj.isEmpty()) {
        m_definationMap.insert(pageObj.value("page").toString(),pageObj);
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
    QList<QJsonObject> listRecord;
    WebAPI::instance()->getJasmineLog(listRecord);
    if(!listRecord.isEmpty()) {
        qDeleteAll(m_listLogRecord);
        m_listLogRecord.clear();
        foreach(QJsonObject logObj , listRecord) {
            m_listLogRecord.append(new LogElement(logObj));
            emit listLogRecordChanged();
        }
    }
}

void AppModel::saveResult()
{
    LOGD << "";
    QJsonArray defArr;
    foreach (QString pageID, m_definationMap.keys()) {
        defArr.append(m_definationMap.value(pageID));
    }

    LOGD << "pageObj: " << defArr;
    if(!defArr.isEmpty()) {
        WebAPI::instance()->saveJamineDefinations(defArr);
    }

    QString outputFilename = QDir::currentPath() + "/../PDT/DataBackup/"
                            + QString::number(QDate::currentDate().year()) + "_"
                            + QString::number(QDate::currentDate().month()) + "_"
                            + QString::number(QDate::currentDate().day()) + "_"
                            + QString::number(QTime::currentTime().hour()) + "_"
                            + QString::number(QTime::currentTime().minute()) + "_"
                            + QString::number(QTime::currentTime().second()) + ".json";
    QFile backupFile(outputFilename);
    if (!backupFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        LOGD << "open fileFail";
        return;
    }
    QTextStream out(&backupFile);
    QJsonDocument doc;
    doc.setArray(defArr);
    out << doc.toJson();
    backupFile.close();
}

void AppModel::getJamineDefinations()
{
    QString defStr;
    WebAPI::instance()->getJamineDefinations(defStr);
    QJsonDocument defDoc = QJsonDocument::fromJson(defStr.toUtf8());
    if(defDoc.isArray()) {
        QJsonArray defArr = defDoc.array();
        for (int i = 0; i < defArr.size(); i++) {
            QJsonObject pageObj = defArr.at(i).toObject();
            if(pageObj.isEmpty()) {
                QMessageBox Msgbox;
                Msgbox.setText("Load Jasmine configuration json file failure!" + defArr.at(i).toString());
                Msgbox.exec();
            }else {
                insertPageDefinations(pageObj);
            }
        }
    } else {
        LOGD << "defDoc is not array";

        QMessageBox Msgbox;
        Msgbox.setText("Load Jasmine configuration json file failure!" + defStr);
        Msgbox.exec();
    }
}

void AppModel::updateJamineDefinations(QString pageID, QString language, QList<QObject *> nodeList)
{
    LOGD << "pageID: " << pageID << " -- langCode: " << language << " -- nodeList: " << nodeList.length();
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
            evidenceItem.insert("clickable",static_cast<ASBLTNode*>(nodeList.at(i))->clickable() == "true"? true : false);
            evidenceItem.insert("checked",static_cast<ASBLTNode*>(nodeList.at(i))->checked() == "true"? true : false);
            evidenceItem.insert("selected",static_cast<ASBLTNode*>(nodeList.at(i))->selected() == "true"? true : false);
            newEvidence.append(evidenceItem);
        }
        if(!arrEdidenceByLange.contains(newEvidence))
            arrEdidenceByLange.append(newEvidence);
        definationsField.insert(language,arrEdidenceByLange);
        pageObj.insert("definitons",definationsField);
        pageObj.insert("page",pageID);
        LOGD << "pageObj: " << pageObj;
        insertPageDefinations(pageObj);
    }
}

void AppModel::updateJamineKeyword(QString pageID, QString language, QList<QObject *> nodeList)
{
    LOGD << "pageID: " << pageID << " -- langCode: " << language << " -- nodeList: " << nodeList.length();
    if(LANG_MAP.contains(language)){
        QJsonObject pageObj = this->getPageDefinations(pageID);
        QJsonObject keywordsField = pageObj.value("keywords").toObject();
        QJsonArray arrKeywordByLang = keywordsField[language].toArray();
        for (int i = 0; i < nodeList.length(); i++) {
            QJsonObject keywordItem;
            keywordItem.insert("text",static_cast<ASBLTNode*>(nodeList.at(i))->text());
            keywordItem.insert("contentDescription",static_cast<ASBLTNode*>(nodeList.at(i))->contentDescription());
            keywordItem.insert("className",static_cast<ASBLTNode*>(nodeList.at(i))->className());
            keywordItem.insert("clickable",static_cast<ASBLTNode*>(nodeList.at(i))->clickable() == "true"? true : false);
            keywordItem.insert("checked",static_cast<ASBLTNode*>(nodeList.at(i))->checked() == "true"? true : false);
            keywordItem.insert("selected",static_cast<ASBLTNode*>(nodeList.at(i))->selected() == "true"? true : false);
            keywordItem.insert("keyword",static_cast<ASBLTNode*>(nodeList.at(i))->keyword());
            if(!arrKeywordByLang.contains(keywordItem))
                arrKeywordByLang.append(keywordItem);
        }
        keywordsField.insert(language,arrKeywordByLang);
        pageObj.insert("keywords",keywordsField);
        pageObj.insert("page",pageID);
        LOGD << "pageObj: " << pageObj;
        insertPageDefinations(pageObj);
    }
}




