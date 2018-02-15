#include <QStringList>
#include <QByteArray>
#include <QDebug>
#include <string>
#include <QThread>
#include <QTcpServer>
#include <QHostAddress>
#include <QSystemSemaphore>
#include <QSettings>
#include <QVariant>
#include <QGuiApplication>

#include "dnai/processmanager.h"

ProcessManager::ProcessManager(QString const &file)
    : QObject(nullptr),
      m_file(file),
      m_server(),
      m_core(),
      m_port(0)
{

}

ProcessManager::~ProcessManager() {
    m_server.close();
    m_core.close();
}

 quint16 ProcessManager::findUnusedPort() const {
     QTcpServer serverTmp;
     quint16 port = 0;

     if (serverTmp.listen(QHostAddress::LocalHost, 0) == false) {
         return port;
     }
     port = serverTmp.serverPort();
     serverTmp.close();

     return port;
 }

void ProcessManager::launch() {
    QSettings settingsBin(m_file, QSettings::IniFormat);

    QStringList argumentsServer;
    QSystemSemaphore sem("SERVER_CORE_DULY", 0, QSystemSemaphore::Create);

    m_port = findUnusedPort();
    if (m_port <= 0) {
        qDebug() << "no port disponible" << m_port;
        return;
    }

    QString serverPath = settingsBin.value("BINARIES/server", "").toString();
    if (serverPath.size() == 0) {
        qDebug() << "failed to launch server from file " << m_file;
        qDebug() << "DO BINARIES/server=\"./PATH/Server\" ";
        return;
    }

    serverPath.replace("{OUT_DIR}", QGuiApplication::applicationDirPath());

    argumentsServer << "-p";
    QString portStr;
    portStr.setNum(m_port);
    argumentsServer << portStr;
    argumentsServer << "-S";
    argumentsServer << sem.key();

    m_server.start(serverPath, argumentsServer);
    if (m_server.waitForStarted() == false) {
        qDebug() << "[FAILED] LAUNCH Server has failed";
        qDebug() << "[FAILED]" << serverPath;
        return;
    }

    sem.acquire();

    QString corePath = settingsBin.value("BINARIES/core", "").toString();
    if (corePath.size() == 0) {
        qDebug() << "failed to launch core from file " << m_file;
        qDebug() << "DO BINARIES/core=\"[mono] ./PATH/CoreDaemon.exe\" ";
        return;
    }

    corePath.replace("{OUT_DIR}", QGuiApplication::applicationDirPath());

    corePath.append(" -p ");
    corePath.append(portStr);

    m_core.start(corePath);
    if (m_core.waitForStarted() == false) {
        qDebug() << "[FAILED] LAUNCH Core has failed";
        qDebug() << "[FAILED]" << corePath;
        return;
    }

    qDebug() << "PROCESSES OK !";
  //  QThread::sleep(10);
}

qint16 ProcessManager::getServerPort() {
    return m_port;
}
