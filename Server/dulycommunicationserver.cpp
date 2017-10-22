#include "headercommunication.h"
#include "dulycommunicationserver.h"

DulyCommunicationServer::DulyCommunicationServer(QTcpSocket *socket)
    : m_socket(socket)
{
    m_packageManager.registerEvent(ADDFunc(*this, &DulyCommunicationServer::onReceiveClientAuthentificationPackage, CLIENT_AUTHENTIFICATION_ID));
    m_packageManager.registerEvent(ADDFunc(*this, &DulyCommunicationServer::onReceiveRegisterEvent, REGISTER_EVENT_ID));
    m_packageManager.registerEvent(ADDFunc(*this, &DulyCommunicationServer::onReceiveSendEvent, SEND_EVENT_ID));
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
    m_packageManager << m_socket->readAll();
    m_packageManager.compute();
}

void DulyCommunicationServer::send(void *data, size_t size) {
    m_socket->write((char *)data, size);
}

// EVENTS

void DulyCommunicationServer::onReceiveClientAuthentificationPackage(void *data, unsigned int size) {
    qDebug() << "CLIENT_AUTHENTIFICATION_ID" << size;
}

void DulyCommunicationServer::onReceiveRegisterEvent(void *, unsigned int size) {
     qDebug() << "REGISTER_EVENT_ID" << size;
}

void DulyCommunicationServer::onReceiveSendEvent(void *, unsigned int size) {
     qDebug() << "SEND_EVENT_ID" << size;
}
