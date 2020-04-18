#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "AppMain.h"
#include <iostream>
#include <CkGlobal.h>
#include <CkHttp.h>
#include <QDir>
#include <QDebug>
#include <AppDefines.h>
#include <QTextCodec>

CkGlobal glob;

bool unlockChilkat();

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    if (unlockChilkat()){
        LOGD << "unlockChilkat successfully";
    } else {
        LOGD << "unlockChilkat Failure";
    }

    AppMain appMain;
    appMain.initApplication();

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("AppModel",AppModel::instance());
    engine.rootContext()->setContextProperty("AppMain",&appMain);
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}


bool unlockChilkat() {
    bool success_global = glob.UnlockBundle("VONGTH.CB4082020_9kru5rnD5R2h");
    if (success_global != true) {
        return false;
    }

    int status = glob.get_UnlockStatus();
    if (status == 2) {
        return true;
    } else {
        return false;
    }
}
