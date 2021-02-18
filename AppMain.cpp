#include "AppMain.h"
#include <WebAPI.hpp>
#include <QFile>
#include <QJsonDocument>

#define APP_MODEL   AppModel::instance()
#define APP_CTRL    AppController::instance()
#define WEB_API     WebAPI::instance()

AppMain::AppMain(QObject *parent) :
    QObject(parent)
{
    LOGD << "CREATED";
     APP_MODEL->getJamineDefinations();
}

AppMain::~AppMain()
{

}

void AppMain::initApplication()
{
    LOGD << "";
}

QJsonDocument AppMain::loadJson(QString fileName)
{
    LOGD << "";
    QFile jsonFile(fileName);
    jsonFile.open(QFile::ReadOnly);
    return QJsonDocument().fromJson(jsonFile.readAll());
}

void AppMain::saveJson(QJsonDocument document, QString fileName)
{
    LOGD << "";
    QFile jsonFile(fileName);
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(document.toJson());
}
