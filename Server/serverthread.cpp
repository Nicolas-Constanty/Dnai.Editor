#include "serverthread.h"

ServerThread::ServerThread(QObject *object)
    : QThread(object),
      m_dulyServer(NULL),
      m_settings("server.ini", QSettings::IniFormat)
{

}

void ServerThread::run() {
    quint16 port = static_cast<quint16>(m_settings.value("Info/port", 8765).toInt());

    m_dulyServer = new DulyServer(port);
    m_dulyServer->start();
    this->exec();
}
