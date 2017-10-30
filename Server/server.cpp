#include "server.h"

Server::Server() :
      m_dulyServer(NULL),
      m_settings("server.ini", QSettings::IniFormat)
{

}

void Server::start() {
    quint16 port = static_cast<quint16>(m_settings.value("Info/port", 8765).toInt());

    m_dulyServer = new DulyServer(port);
    m_dulyServer->start();
   // this->exec();
}
