#include "include/clientmanager.h"
#include "include/dnai/controllers/clientcontroller.h"

#include "dnai/commands/core/declare.h"
#include "dnai/corepackages/replies/declarator/declared.h"

namespace dnai
{
	namespace controllers
	{
		qint16 ClientController::serverPort = 7777;

        ClientController::ClientController() :
            m_clientCom(nullptr),
			m_name(CLIENT_NAME),
			m_port(ClientController::serverPort),
			m_addr(QHostAddress::LocalHost)
		{
            m_clientCom = ClientManager::shared().newClient(m_addr, m_port, m_name);

            registerReplyEvent<corepackages::declarator::Declared>([](corepackages::declarator::Declared const &reply) {
                qDebug() << "My amazing registered";

                qDebug() << QString("Declarator.Declare(")
                         << reply.command.declarator
                         << QString(", ")
                         << static_cast<qint32>(reply.command.type)
                         << QString(", ")
                         << reply.command.name
                         << QString(", ")
                         << static_cast<qint32>(reply.command.visibility)
                         << QString(");");
                qDebug() << QString("===> ") << reply.declared;
            });
		}

        ClientController &ClientController::shared()
        {
			static ClientController clientController;

			return clientController;
        }
	}
}
