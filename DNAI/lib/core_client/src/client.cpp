#include "clientmanager.h"
#include "client.h"

namespace core
{
    qint16 Client::serverPort = 7777;
    QString Client::clientName = "DNAI_GUI";

    Client::Client() :
        m_clientCom(nullptr),
        m_name(Client::clientName),
        m_port(Client::serverPort),
        m_addr(QHostAddress::LocalHost)
    {
        m_clientCom = ClientManager::shared().newClient(m_addr, m_port, m_name);
    }

    Client &Client::shared()
    {
        static Client coreClient;

        return coreClient;
    }
}
