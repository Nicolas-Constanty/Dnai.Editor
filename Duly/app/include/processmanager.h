#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <QProcess>
#include <QObject>
#include <QString>

class ProcessManager : public QObject {
    Q_OBJECT

public:
    ProcessManager(QString const &path);
    ~ProcessManager();

    void launch();

public:
    qint16 getServerPort();

public slots:
    void readData();

private:
    QString m_path;
    QProcess m_server;
    QProcess m_core;
    qint16 m_port;
};

#endif // PROCESSMANAGER_H
