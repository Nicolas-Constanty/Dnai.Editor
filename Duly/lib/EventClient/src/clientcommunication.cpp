#include "authentificationpackage.h"
#include "clientcommunication.h"

ClientCommunication::ClientCommunication(QHostAddress addr,
                                         quint16 port,
                                         QString name)
    : QThread(nullptr),
      m_com(nullptr),
      m_addr(addr),
      m_port(port),
      m_name(name),
      m_sem()
{
    qRegisterMetaType<unsigned int>();
    connect(this, SIGNAL(runStarted()), this, SLOT(onRunStarted()));
}

void ClientCommunication::onRunStarted() {
    connect(m_com, SIGNAL(receiveSendEventSignal(QByteArray *)),
            this, SLOT(onReceiveSendEventSignal(QByteArray *)), Qt::QueuedConnection);
}

void ClientCommunication::onReceiveSendEventSignal(QByteArray *bytes) {
    EventSendFromClientPackage *eventSendInfo = (EventSendFromClientPackage *)bytes->data();

    QString name(eventSendInfo->eventName);

    static std::hash<std::string> h1;

    size_t str_hash = h1(name.toStdString());
    std::map<size_t, EventCallBack>::iterator it = m_eventsRegister.find(str_hash);

    if (it != m_eventsRegister.end()) {
        it->second.func((void *)((char *)(bytes->data()) + sizeof(EventSendFromClientPackage)), bytes->size() - sizeof(EventSendFromClientPackage));
    }

    delete bytes;

}

void ClientCommunication::sendEvent(QString const &name, void *data, unsigned int size) {

    SendEventSendFromClientPackage *eventSendPackage = createEventSendFromClientPackage(name, data, size);

    emit m_com->sendDataAllocated(eventSendPackage, sizeof(SendEventSendFromClientPackage) + size);
}

void ClientCommunication::registerEvent(QString const &eventName,
                   unsigned int size,
                   std::function<void (void *, unsigned int)> func) {
    static std::hash<std::string> h1;

    size_t str_hash = h1(eventName.toStdString());

    if (!m_com)
        m_sem.acquire();


    m_eventsRegister.emplace(str_hash, EventCallBack(eventName, func));

    SendEventRegisterPackage *eventRegister2 = (SendEventRegisterPackage *)malloc(sizeof(SendEventRegisterPackage));
    createEventRegisterPackage(*eventRegister2, eventName, size, true);
    emit m_com->sendDataAllocated(eventRegister2, sizeof(*eventRegister2));
}


void ClientCommunication::run() {
   // qDebug() << "OK";
    QTcpSocket *socket = new QTcpSocket();
    socket->connectToHost(m_addr, m_port);

    m_com = new DulyCommunicationServer(socket);

    socket->moveToThread(this);
    m_com->moveToThread(this);

    m_com->start();

    SendAuthenticatePackage data;
    createAuthenticatePackage(data, m_name);
    m_com->send(&data, sizeof(data));





    emit runStarted();
    m_sem.release();
    this->exec();
}
