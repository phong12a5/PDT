#ifndef APPDEFINES_H
#define APPDEFINES_H

#include <QDebug>
#include <QEventLoop>
#include <QTimer>


#define LOGD qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]"

inline void delay(int ms){
    QEventLoop even;
    QTimer timer;
    timer.setInterval(ms);
    timer.setSingleShot(true);
    QObject::connect(&timer, SIGNAL(timeout()), &even, SLOT(quit()));
    timer.start();
    even.exec();
}

#endif // APPDEFINES_H
