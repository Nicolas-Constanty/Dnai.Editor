#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include <QThread>
#include <QSettings>
#include "dulyserver.h"

class Server
{
public:
    Server();

public:
    void start();

private:
    DulyServer *m_dulyServer;
    QSettings m_settings;
    // SERVER
};

#endif // SERVERTHREAD_H
