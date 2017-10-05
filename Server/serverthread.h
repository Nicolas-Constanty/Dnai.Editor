#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include <QThread>
#include <QSettings>
#include "dulyserver.h"

class ServerThread : public QThread
{
    Q_OBJECT

public:
    ServerThread(QObject *object = 0);

protected:
    void run();

private:
    DulyServer *m_dulyServer;
    QSettings m_settings;
    // SERVER
};

#endif // SERVERTHREAD_H
