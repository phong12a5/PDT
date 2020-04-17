#ifndef APPMODEL_H
#define APPMODEL_H

#include <QObject>
#include "AppDefines.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <CkJsonArray.h>

/*[android.view.accessibility.AccessibilityNodeInfo@a287;
 * boundsInParent: Rect(0, 0 - 126, 38);
 * boundsInScreen: Rect(165, 426 - 291, 464);
 * packageName: com.facebook.katani;
 * className: android.view.ViewGroup;
 * text: Ti\\u1ebfng Vi\\u1ec7t;
 * error: null; maxTextLength: -1;
 * contentDescription: Ti\\u1ebfng Vi\\u1ec7t;
 * tooltipText: null;
 * viewIdResName: null;
 * checkable: false;
 * checked: false;
 * focusable: false;
 * focused: false;
 * selected: false;
 * clickable: true;
 * longClickable: false;
 * contextClickable: false;
 * enabled: true; password: false;
 * scrollable: false;
 * importantForAccessibility:
 * true; visible: true;
 * actions: [AccessibilityAction: ACTION_SELECT - null, AccessibilityAction: ACTION_CLEAR_SELECTION - null, AccessibilityAction: ACTION_CLICK - null, AccessibilityAction: ACTION_ACCESSIBILITY_FOCUS - null, AccessibilityAction: ACTION_NEXT_AT_MOVEMENT_GRANULARITY - null, AccessibilityAction: ACTION_PREVIOUS_AT_MOVEMENT_GRANULARITY - null, AccessibilityAction: ACTION_SHOW_ON_SCREEN - null]*/
class ASBLTNode : public QObject {

    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(QString contentDescription READ contentDescription WRITE setContentDescription NOTIFY contentDescriptionChanged)
public:
    explicit ASBLTNode(QString nodeStr) {
        QStringList listProp = nodeStr.split(";");
        foreach(QString pair, listProp) {
            QStringList map = pair.split(": ");
            if(map.length() == 2) {
                QString propName = map.at(0).simplified();
                QString value = map.at(1);
                this->setProperty(propName.toLocal8Bit().data(),QVariant(value));
//                LOGD << propName << " : " << property(propName.toLocal8Bit().data());
            }
        }
    }

private:
    QString m_text;
    QString m_contentDescription;

public:
    QString text() const {return m_text;}
    void setText(QString text) {
        LOGD << text;
        m_text = text;
        emit textChanged();
    }

    QString contentDescription() const {return  m_contentDescription;}
    void setContentDescription(QString contentDescription) {
        LOGD << contentDescription;
        m_contentDescription = contentDescription;
        emit contentDescriptionChanged();
    }

signals:
    void textChanged();
    void contentDescriptionChanged();
};

class LogElement: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString token READ token NOTIFY tokenChanged)
    Q_PROPERTY(QString dateTime READ dateTime NOTIFY dateTimeChanged)
    Q_PROPERTY(QString info READ info NOTIFY infoChanged)
    Q_PROPERTY(QString deviceName READ deviceName NOTIFY deviceNameChanged)
    Q_PROPERTY(QString module READ module NOTIFY moduleChanged)
    Q_PROPERTY(QString className READ className NOTIFY classNameChanged)
    Q_PROPERTY(QString tag READ tag NOTIFY tagChanged)
    Q_PROPERTY(QString page READ page NOTIFY pageChanged)
    Q_PROPERTY(QList<QObject*> acsblNodeList READ acsblNodeList NOTIFY acsblNodeListChanged)

private:
    QString m_token;
    QString m_dateTime;
    QString m_info;
    QString m_deviceName;
    QString m_module;
    QString m_className;
    QString m_tag;
    QString m_page;
    QString m_acsblNodeListStr;
    QList<QObject*> m_acsblNodeList;

public:
    explicit LogElement(QJsonObject logJObj) {
        if(logJObj.contains("token")){
            m_token = logJObj.value("token").toString();
        }
        if(logJObj.contains("dateTime")){
            m_dateTime = logJObj.value("dateTime").toString();
        }
        if(logJObj.contains("info")){
            m_info = logJObj.value("info").toString();
        }
        if(logJObj.contains("devicename")){
            m_deviceName = logJObj.value("devicename").toString();
        }
        if(logJObj.contains("module")){
            m_module = logJObj.value("module").toString();
        }
        if(logJObj.contains("class")){
            m_className = logJObj.value("class").toString();
        }
        if(logJObj.contains("tag")){
            m_tag = logJObj.value("tag").toString();
        }
        if(logJObj.contains("page")){
            m_page = logJObj.value("page").toString();
        }
        if(logJObj.contains("message")){
            m_acsblNodeListStr = logJObj.value("message").toString();
            QJsonArray array = QJsonDocument::fromJson(m_acsblNodeListStr.toLocal8Bit()).array();
            qDeleteAll(m_acsblNodeList);

            CkJsonArray arr;
            arr.Load(m_acsblNodeListStr.toLocal8Bit().data());
            for (int i = 0; i < arr.get_Size(); i ++) {
                m_acsblNodeList.append(new ASBLTNode(arr.stringAt(i)));
            }
            LOGD << "m_acsblNodeList size: " << m_acsblNodeList.size();
        }
    }

    ~LogElement() {
        qDeleteAll(m_acsblNodeList);
    }

public:
    QString token() const {return m_token;}
    QString dateTime() const {return m_dateTime;}
    QString info() const {return m_info;}
    QString deviceName() const {return m_acsblNodeListStr;}
    QString module() const {return m_module;}
    QString className() const {return m_className;}
    QString tag() const {return m_tag;}
    QString page() const {return m_page;}
    QList<QObject*> acsblNodeList() const {return m_acsblNodeList;}

signals:
    void tokenChanged();
    void dateTimeChanged();
    void infoChanged();
    void deviceNameChanged();
    void moduleChanged();
    void classNameChanged();
    void tagChanged();
    void pageChanged();
    void acsblNodeListChanged();
};

class AppModel : public QObject
{
    Q_OBJECT


private:
    explicit AppModel(QObject *parent = nullptr);
    Q_PROPERTY(QList<QObject*> listLogRecord READ listLogRecord NOTIFY listLogRecordChanged)

public:
    static AppModel* instance();

    QList<QObject*> listLogRecord();

public:
    Q_INVOKABLE void getLogFromServer();

signals:
    void listLogRecordChanged();

private:
    static AppModel* m_instance;

    QList<QObject*> m_listLogRecord;

public slots:
};

#endif // APPMODEL_H
