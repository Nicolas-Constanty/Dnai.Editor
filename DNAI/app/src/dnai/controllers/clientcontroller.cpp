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
            });

            m_clientCom->registerEvent("ERROR", 0, [this](void *data, int size) {
                Cerealization::Cerealizer::BinaryStream stream((Cerealization::Cerealizer::BinaryStream::Byte *)data, size);

                QString message;
                std::string event = m_eventQueue.front();

                stream >> message;

                qDebug() << "Error on event " << event.c_str() << ": " << message;
                m_eventQueue.pop();
            });
		}

        ClientController &ClientController::shared()
        {
			static ClientController clientController;

			return clientController;
        }
	}
}
