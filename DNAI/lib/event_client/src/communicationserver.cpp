#include "headercommunication.h"
#include "communicationserver.h"
#include "authentificationpackage.h"
#include "eventregisterpackage.h"
#include "eventsendpackage.h"
#if SERVER_MODE
#include "eventmanager.h"
#endif

CommunicationServer::CommunicationServer(QTcpSocket *socket,
                                                 std::list<CommunicationServer *> *clients)
    : QObject(nullptr),
      m_socket(socket),
      m_packageManager(),
      m_authenticated(false),
      m_name(),
      m_clients(clients)

{
    m_packageManager.registerEvent(ADDFunc(this, &CommunicationServer::onReceiveClientAuthentificationPackage, CLIENT_AUTHENTIFICATION_ID));
    m_packageManager.registerEvent(ADDFunc(this, &CommunicationServer::onReceiveRegisterEvent, REGISTER_EVENT_ID));
    m_packageManager.registerEvent(ADDFunc(this, &CommunicationServer::onReceiveSendEvent, SEND_EVENT_ID));

}

CommunicationServer::CommunicationServer(CommunicationServer const &other) : QObject(nullptr) {
    *this = other;
}

CommunicationServer &CommunicationServer::operator=(CommunicationServer const &other) {
    this->m_socket = other.m_socket;

    return (*this);
}

QTcpSocket *CommunicationServer::socket() {
    return (m_socket);
}

void CommunicationServer::setSocket(QTcpSocket *socket) {
    m_socket = socket;
}

void CommunicationServer::start() {
    qDebug() << "[INFO] connection start !";
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(onRead()));
    connect(this, SIGNAL(sendData(void*,unsigned int)), this, SLOT(send(void*,unsigned int)));
    connect(this, SIGNAL(sendDataAllocated(void*,uint)), this, SLOT(sendAllocatedData(void*,uint)));
  //  useless();
}

void CommunicationServer::onDisconnected() {
    emit clientDisconnected(this);
}

void CommunicationServer::onRead() {
    m_packageManager << m_socket->readAll();
    m_packageManager.compute();
}

void CommunicationServer::send(void *data, unsigned int size) {
    m_socket->write((char *)data, size);
}

void CommunicationServer::sendAllocatedData(void *data, unsigned int size) {
    send(data, size);
    free(data);
}

void CommunicationServer::sendEventRegisterToAllClient(SendEventRegisterPackageAnswerServer &eventRegisterAnswerServer) {

    if (!m_clients) {
        qDebug() << "m_clients is nil";
        return;
    }

    std::list<CommunicationServer *>::iterator it = m_clients->begin();

    while (it != m_clients->end()) {
        (*it)->send(&eventRegisterAnswerServer, sizeof(eventRegisterAnswerServer));
        ++it;
    }
}

// EVENTS

void CommunicationServer::onReceiveClientAuthentificationPackage(void *data, unsigned int size) {

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



void CommunicationServer::onReceiveRegisterEvent(void *data, unsigned int size) {
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

void CommunicationServer::onReceiveSendEvent(void *data, unsigned int size) {
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
