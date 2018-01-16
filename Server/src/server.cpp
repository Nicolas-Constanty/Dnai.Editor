#include "server.h"

Server::Server(bool randomPort, qint16 port, QString const &semKey) :
      m_dulyServer(NULL),
      m_settings("server.ini", QSettings::IniFormat),
      m_randomPort(randomPort),
      m_port(port),
      m_semKey(semKey)
{

}

void Server::start() {
    quint16 port = static_cast<quint16>(m_settings.value("Info/port", 8765).toInt());
    if (m_randomPort)
        port = 0;
    else {
        port = m_port;
    }

    m_dulyServer = new DulyServer(port, QHostAddress::LocalHost);
    m_dulyServer->start(m_semKey);
   // this->exec();
}
