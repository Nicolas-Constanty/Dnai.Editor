#ifndef DULYCOMMUNICATIONSERVER_H
#define DULYCOMMUNICATIONSERVER_H

#include <QObject>
#include <QTcpSocket>

class DulyCommunicationServer : public QObject
{
    Q_OBJECT

public:
    DulyCommunicationServer(QTcpSocket *socket);
    DulyCommunicationServer(DulyCommunicationServer const &);

    DulyCommunicationServer &operator=(DulyCommunicationServer const &);

public:
    void start();

public slots:
    void onRead();

private:
    QTcpSocket *m_socket;
};

#endif // DULYCOMMUNICATIONSERVER_H
