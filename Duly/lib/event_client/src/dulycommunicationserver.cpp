#include "headercommunication.h"
#include "dulycommunicationserver.h"
#include "authentificationpackage.h"
#include "eventregisterpackage.h"
#include "eventsendpackage.h"
#if SERVER_MODE
#include "eventmanager.h"
#endif

DulyCommunicationServer::DulyCommunicationServer(QTcpSocket *socket,
                                                 std::list<DulyCommunicationServer *> *clients)
    : QObject(nullptr),
      m_socket(socket),
      m_packageManager(),
      m_authenticated(false),
      m_name(),
      m_clients(clients)

{
    m_packageManager.registerEvent(ADDFunc(this, &DulyCommunicationServer::onReceiveClientAuthentificationPackage, CLIENT_AUTHENTIFICATION_ID));
    m_packageManager.registerEvent(ADDFunc(this, &DulyCommunicationServer::onReceiveRegisterEvent, REGISTER_EVENT_ID));
    m_packageManager.registerEvent(ADDFunc(this, &DulyCommunicationServer::onReceiveSendEvent, SEND_EVENT_ID));

}

DulyCommunicationServer::DulyCommunicationServer(DulyCommunicationServer const &other) : QObject(nullptr) {
    *this = other;
}

DulyCommunicationServer &DulyCommunicationServer::operator=(DulyCommunicationServer const &other) {
    this->m_socket = other.m_socket;

    return (*this);
}

QTcpSocket *DulyCommunicationServer::socket() {
    return (m_socket);
}

void DulyCommunicationServer::setSocket(QTcpSocket *socket) {
    m_socket = socket;
}

void DulyCommunicationServer::start() {
    qDebug() << "[INFO] connection start !";
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(onRead()));
    connect(this, SIGNAL(sendData(void*,unsigned int)), this, SLOT(send(void*,unsigned int)));
    connect(this, SIGNAL(sendDataAllocated(void*,uint)), this, SLOT(sendAllocatedData(void*,uint)));
  //  useless();
}

void DulyCommunicationServer::onDisconnected() {
    emit clientDisconnected(this);
}

void DulyCommunicationServer::onRead() {
    m_packageManager << m_socket->readAll();
    m_packageManager.compute();
}

void DulyCommunicationServer::send(void *data, unsigned int size) {
    m_socket->write((char *)data, size);
}

void DulyCommunicationServer::sendAllocatedData(void *data, unsigned int size) {
    send(data, size);
    free(data);
}

void DulyCommunicationServer::sendEventRegisterToAllClient(SendEventRegisterPackageAnswerServer &eventRegisterAnswerServer) {

    if (!m_clients) {
        qDebug() << "m_clients is nil";
        return;
    }

    std::list<DulyCommunicationServer *>::iterator it = m_clients->begin();

    while (it != m_clients->end()) {
        (*it)->send(&eventRegisterAnswerServer, sizeof(eventRegisterAnswerServer));
        ++it;
    }
}

// EVENTS

void DulyCommunicationServer::onReceiveClientAuthentificationPackage(void *data, unsigned int size) {

#if SERVER_MODE
    if (size != sizeof(AuthentificationPackage) || m_authenticated == true) {
        qDebug() << "Connection failed";
        m_socket->close();
        return;
    }

    AuthentificationPackage *auth = (AuthentificationPackage *)data;
    m_name = auth->name;
    m_authenticated = true;

    qDebug() << "[INFO] " << m_name << " is connected";

#endif
    (void)data;
    (void)size;

}



void DulyCommunicationServer::onReceiveRegisterEvent(void *data, unsigned int size) {
#if SERVER_MODE
     if (size != sizeof(EventRegisterPackage)) {
         return;
     }
     EventRegisterPackage *eventRegister = (EventRegisterPackage *)data;

     QString name(eventRegister->eventName);

    qDebug() << "[INFO] " << this->m_name << " register " << name << " event !";

     EventManager::shared().addClientToEvent(name, eventRegister->eventSize, this);

#endif
     (void)data;
     (void)size;
}

void DulyCommunicationServer::onReceiveSendEvent(void *data, unsigned int size) {
#if SERVER_MODE

     if (size < sizeof(EventSendFromClientPackage)) {
         return;
     }

    EventSendFromClientPackage *eventSendPackage = (EventSendFromClientPackage *)data;

    qDebug() << "[INFO] " << this->m_name << " receive " << eventSendPackage->eventName << " event";

    try {
        EventManager::Event &event = EventManager::shared().getFrom(eventSendPackage->eventName);
        if (event.getSize() != size - sizeof(EventSendFromClientPackage)) {
            qDebug() << "[WARNING] receive bad size from " << eventSendPackage->eventName;
            return;
        }
        event.compute((void *)((char *)data - sizeof(HeaderCommunication)), size + sizeof(HeaderCommunication));

        static int i = 0;
        qDebug() << "[INFO] packet number: " << i;
        ++i;

    } catch (std::runtime_error &err) {
        qDebug() << err.what();
    }
#else

     if (size < sizeof(EventSendFromClientPackage)) {
         return;
     }

    QByteArray *bytes = new QByteArray((char *)data, size);

    emit receiveSendEventSignal(bytes);
#endif
}
