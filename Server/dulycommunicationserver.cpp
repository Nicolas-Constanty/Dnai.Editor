#include "packagemanager.h"
#include "dulycommunicationserver.h"

DulyCommunicationServer::DulyCommunicationServer(QTcpSocket *socket)
    : m_socket(socket)
{

}

DulyCommunicationServer::DulyCommunicationServer(DulyCommunicationServer const &other) {
    *this = other;
}

DulyCommunicationServer &DulyCommunicationServer::operator=(DulyCommunicationServer const &other) {
    this->m_socket = other.m_socket;

    return (*this);
}

QTcpSocket *DulyCommunicationServer::socket() {
    return (m_socket);
}

void DulyCommunicationServer::start() {
    qDebug() << "[INFO] connection start !";
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(onRead()));
}

void DulyCommunicationServer::onRead() {
    PackageManager<DulyCommunicationServer> packageManager;
    qDebug() << m_socket->readBufferSize();
    // note that QByteArray can be casted to char * and const char *
    QByteArray data = m_socket->readAll();

    packageManager << data;

    qDebug() << data;
}
