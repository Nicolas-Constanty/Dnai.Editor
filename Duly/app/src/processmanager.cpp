#include <QStringList>
#include <QByteArray>
#include <QDebug>
#include <string>
#include <QThread>
#include <QTcpServer>
#include <QHostAddress>
#include <QSystemSemaphore>
#include "processmanager.h"

ProcessManager::ProcessManager(QString const &path)
    : QObject(nullptr),
      m_path(path),
      m_server(),
      m_core(),
      m_port(0)
{

}

ProcessManager::~ProcessManager() {
    m_server.close();
}

 void ProcessManager::readData() {
     m_server.waitForBytesWritten();
 }

void ProcessManager::launch() {
    QStringList argumentsServer;
    QSystemSemaphore sem("SERVER_CORE_DULY", 0, QSystemSemaphore::Create);

    QTcpServer serverTmp;

    if (serverTmp.listen(QHostAddress::LocalHost, 0) == false) {
        qDebug() << "FAILED";
        return;
    }

    argumentsServer << "-p";
    QString portStr;
    portStr.setNum(serverTmp.serverPort());
    m_port = serverTmp.serverPort();
    argumentsServer << portStr;
    argumentsServer << "-S";
    argumentsServer << sem.key();

    serverTmp.close();

    m_server.startDetached(m_path + "/ServerDir/Server", argumentsServer);

    sem.acquire();

    QString coreStr("/Library/Frameworks/Mono.framework/Versions/Current/Commands/mono ./bin/Core/CoreDaemon.exe");
    coreStr.append(" -p ");
    coreStr.append(portStr);
    m_core.startDetached(coreStr);
}

qint16 ProcessManager::getServerPort() {
    return m_port;
}
