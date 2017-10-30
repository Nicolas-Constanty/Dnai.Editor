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
   // connect(this, SIGNAL(sendEvent(QString,void*,uint)),
   //         this, SLOT(onSendEvent(QString,void*,uint)), Qt::QueuedConnection);
}

void ClientCommunication::onRunStarted() {
 //   qDebug() << "onRunStarted start";
    connect(m_com, SIGNAL(receiveSendEventSignal(QByteArray *)),
            this, SLOT(onReceiveSendEventSignal(QByteArray *)), Qt::QueuedConnection);
    //connect(m_com, SIGNAL(reveiveNewEventName(QString, unsigned int)),
    //        this, SLOT(onReveiveNewEventName(QString, unsigned int)), Qt::QueuedConnection);
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

//void ClientCommunication::onReveiveNewEventName(QString name, unsigned int id) {
    /*return;

    if (id < m_events.size()) {
        return;
     //   m_events[id] = EventCallBack(name, std::function<void (void *, unsigned int)>());
    }

    QList<EventCallBack>::iterator it = m_eventsUnk.begin();
    while (it != m_eventsUnk.end()) {
        if ((*it).name == name) {
            m_events.push_back((*it));
            m_eventsUnk.erase(it);
            return;
        }
        ++it;
    }
    if (m_events.size() == id) {
        m_events.push_back(EventCallBack(name, std::function<void (void *, unsigned int)>()));
    } else {
        qDebug() << "ERROR push_back event " << id << " name : " << name;
    }
    //m_events.push_back(EventCallBack(name, m_func));*/
//}

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
