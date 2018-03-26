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

        /*registerReplyEvent<corepackages::declarator::Declared>(
            [](corepackages::declarator::Declared const &reply) {
                qDebug() << "My amazing registered";

                qDebug() << "Declarator.Declare("
                         << reply.command.declarator
                         << ", "
                         << static_cast<qint32>(reply.command.type)
                         << ", "
                         << reply.command.name
                         << ", "
                         << static_cast<qint32>(reply.command.visibility)
                         << ");";
                qDebug() << "===> " << reply.declared;
            },
            [](corepackages::ErrorReply<corepackages::declarator::Declare> const &error) {
                qDebug()
                        << "Error on event declarator::declare("
                        << error.command.declarator << ", "
                        << error.command.type << ", "
                        << error.command.name << ", "
                        << error.command.visibility << "): " << error.message;
            }
        );*/
    }

    Client &Client::shared()
    {
        static Client coreClient;

        return coreClient;
    }
}
