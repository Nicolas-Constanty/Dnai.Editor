#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include <QThread>
#include <QSettings>
#include "dulyserver.h"

class Server
{
public:
    Server(bool randomPort, qint16 port, QString const &semKey);

public:
    void start();

private:
    DulyServer *m_dulyServer;
    QSettings m_settings;
    bool    m_randomPort;
    qint16 m_port;
    QString m_semKey;
    // SERVER
};

#endif // SERVERTHREAD_H
