#ifndef DULYCOMMUNICATIONSERVER_H
#define DULYCOMMUNICATIONSERVER_H

#include <QObject>
#include <QTcpSocket>
#include "packagemanager.h"

#define ADDFunc(obj, func, id) std::bind(func, obj, std::placeholders::_1, std::placeholders::_2), id

class DulyCommunicationServer : public QObject
{
    Q_OBJECT

public:
    DulyCommunicationServer(QTcpSocket *socket);
    DulyCommunicationServer(DulyCommunicationServer const &);

    DulyCommunicationServer &operator=(DulyCommunicationServer const &);

public:
    void start();
    QTcpSocket *socket();

    void send(void *, size_t size);

private:
    void onReceiveClientAuthentificationPackage(void *, unsigned int size);
    void onReceiveRegisterEvent(void *, unsigned int size);
    void onReceiveSendEvent(void *, unsigned int size);

public slots:
    void onRead();

private:
    QTcpSocket *m_socket;
    PackageManager m_packageManager;
};

#endif // DULYCOMMUNICATIONSERVER_H
