#include <QDebug>
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

void DulyServer::start() {
    connect(this, SIGNAL(newConnection()), this, SLOT(connectionAccepted()));

    if (this->listen(m_address, m_port) == false) {
        qDebug() << "[ERROR] Failed to start server !";
        qDebug() << "[ERROR] port: " << m_port;
        qDebug() << "[ERROR] ip: " << m_address;
    } else {
        qDebug() << "[SUCCESS] Server start !";
        qDebug() << "[SUCCESS] port: " << m_port;
        qDebug() << "[SUCCESS] ip: " << m_address;
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
