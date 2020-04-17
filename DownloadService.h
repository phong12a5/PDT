#ifndef DOWNLOADSERVICE_H
#define DOWNLOADSERVICE_H

#include <QObject>
#include <QThread>
#include <AppDefines.h>

class DownloadService : public QObject
{
    Q_OBJECT
public:
    explicit DownloadService(QObject *parent = nullptr);

private:
    QThread* m_thread;

signals:
    void startService();

private:
    QMap<QString, QString> getListContentOfFolder(QString folderPath);
    bool downloadTrainedData(QString langCode);
    void downloadApp();

public slots:
    void onStartService();
};

#endif // DOWNLOADSERVICE_H
