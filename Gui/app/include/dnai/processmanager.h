#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <QProcess>
#include <QObject>
#include <QString>

class ProcessManager : public QObject {
    Q_OBJECT

public:
    ProcessManager(QString const &file = "");
    ~ProcessManager();

    void launch();
    void launchUpdater(QString const &actualVer, QString const &newVersion);
    void closeAll();

private:
    quint16 findUnusedPort() const;

public:
    quint16 getServerPort();

    void setFile(const QString &file);

private slots:
    void setTimeOut();
private:
    QString m_file;
    QProcess m_server;
    QProcess m_core;
    QString m_updaterApp;
    quint16 m_port;
    bool m_isTimeOut;
};

#endif // PROCESSMANAGER_H
