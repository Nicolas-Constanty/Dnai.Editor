#ifndef DULYSERVER_H
#define DULYSERVER_H

#include <QTcpServer>
#include <list>
#include "dulycommunicationserver.h"

class DulyServer : public QTcpServer
{
    Q_OBJECT

public:
    DulyServer(quint16 port = 0, const QHostAddress &address = QHostAddress::LocalHost, QObject *parent = Q_NULLPTR);

public:
    void start();

public slots:
    void connectionAccepted();
    void onClientDisconnect();
    void onClientDisconnected(DulyCommunicationServer *);

private:
    quint16 m_port;
    QHostAddress m_address;
    std::list<DulyCommunicationServer *> m_clients;

};

#endif // DULYSERVER_H
