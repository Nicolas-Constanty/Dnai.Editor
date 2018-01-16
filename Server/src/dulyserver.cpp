#include <QDebug>
#include <QFile>
#include <QSystemSemaphore>
#include "dulyserver.h"
#include "eventmanager.h"

DulyServer::DulyServer(quint16 port,
                       const QHostAddress &address,
                       QObject *parent)
    : QTcpServer(parent),
      m_port(port),
      m_address(address)
{

}

void DulyServer::createFileInfo(bool failed) {
    QString filename="currentport.info";

    QFile::remove(filename);
    QFile file( filename );
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        if (failed == true) {
            stream << "FAILED" << endl;
        } else {
            stream << this->serverPort() << endl;
        }
    }
}

void DulyServer::start(QString const &semKey) {
    connect(this, SIGNAL(newConnection()), this, SLOT(connectionAccepted()));

    if (this->listen(m_address, m_port) == false) {
        qDebug() << "[ERROR] Failed to start server !";
    } else {
        qDebug() << "[SUCCESS] Server start !";
        qDebug() << "[SUCCESS] port: " << this->serverPort();
        qDebug() << "[SUCCESS] ip: " << m_address;
    }
    if (semKey.size() > 0) {
        QSystemSemaphore sem(semKey, 0, QSystemSemaphore::Open);
        sem.release();
    }
}

void DulyServer::onClientDisconnected(DulyCommunicationServer *client) {
    qDebug() << "[INFO] client disconnected";
    EventManager::shared().removeClient(client);
    m_clients.remove(client);
}

void DulyServer::onClientDisconnect() {
}

void DulyServer::connectionAccepted() {
    QTcpSocket *socket = this->nextPendingConnection();
    DulyCommunicationServer *newCommunication = new DulyCommunicationServer(socket, &m_clients);

    qDebug() << "[INFO] new connection !";

    connect(socket, SIGNAL(disconnected()), newCommunication, SLOT(onDisconnected()));
    connect(newCommunication, SIGNAL(clientDisconnected(DulyCommunicationServer*)), this, SLOT(onClientDisconnected(DulyCommunicationServer*)));

    newCommunication->start();
    m_clients.push_back(newCommunication);
}
