#ifndef COMMUNICATIONSERVER_H
#define COMMUNICATIONSERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <QQueue>
#include "packagemanager.h"
#include <vector>
#include <list>

#include "eventsendpackage.h"
#include "eventregisterpackage.h"

#define ADDFunc(obj, func, id) std::bind(func, obj, std::placeholders::_1, std::placeholders::_2), id

Q_DECLARE_METATYPE(unsigned int)

class CommunicationServer : public QObject
{
    Q_OBJECT

public:
    CommunicationServer(QObject *parent = nullptr) : QObject(parent) {}
    CommunicationServer(QTcpSocket *socket = 0, std::list<CommunicationServer *> *clients = 0);
    CommunicationServer(CommunicationServer const &);

    CommunicationServer &operator=(CommunicationServer const &);

//#ifndef SERVER_MODE
signals:
    void receiveSendEventSignal(QByteArray *);
    void sendData(void *, unsigned int size);
    void sendDataAllocated(void *, unsigned int size);

//#endif

signals:
    void clientDisconnected(CommunicationServer *);

public:
    void setSocket(QTcpSocket *socket);
    void start();
    QTcpSocket *socket();

public slots:
    void send(void *, unsigned int size);
    void sendAllocatedData(void *, unsigned int size);
    void onRead();
    void onDisconnected();

private:
    void onReceiveClientAuthentificationPackage(void *, unsigned int size);
    void onReceiveRegisterEvent(void *, unsigned int size);
    void onReceiveSendEvent(void *, unsigned int size);

private:
    void sendEventRegisterToAllClient(SendEventRegisterPackageAnswerServer &);

private:
    QTcpSocket *m_socket;
    PackageManager m_packageManager;
    bool        m_authenticated;
    QString     m_name;
    std::list<CommunicationServer *> *m_clients;
};

#endif // COMMUNICATIONSERVER_H
