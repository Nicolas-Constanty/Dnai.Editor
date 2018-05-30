#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <QProcess>
#include <QObject>
#include <QString>

class ProcessManager : public QObject {
    Q_OBJECT

public:
    ProcessManager(QString const &file);
    ~ProcessManager();

    void launch();
    void launchUpdater(QString const &actualVer, QString const &newVersion);
    void closeAll();

private:
    quint16 findUnusedPort() const;

public:
    qint16 getServerPort();

private:
    QString m_file;
    QProcess m_server;
    QProcess m_core;
    QString m_updaterApp;
    quint16 m_port;
};

#endif // PROCESSMANAGER_H
