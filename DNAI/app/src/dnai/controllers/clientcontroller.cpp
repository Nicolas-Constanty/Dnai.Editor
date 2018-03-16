#include "include/clientmanager.h"
#include "include/clientcommunication.h"
#include "include/dnai/controllers/clientcontroller.h"
#include "commands/commands.h"
#include "replies/replies.h"

namespace dnai
{
	namespace controllers
	{
		qint16 ClientController::serverPort = 7777;

		ClientController::ClientController()
			: m_clientCom(nullptr),
			m_dataComFactory(new DataComEventFactory()),
			m_name(CLIENT_NAME),
			m_port(ClientController::serverPort),
			m_addr(QHostAddress::LocalHost)
		{
			m_clientCom = ClientManager::shared().newClient(m_addr,
				m_port,
				m_name);

            registerReplyEvent<Reply::Declarator::Declared>([](EntityID declarator, ENTITY_CORE type, std::string const &name, VISIBILITYCORE visibility, EntityID declared) {
                qDebug() << "My amazing registered";

                qDebug() << QString("Declarator.Declare(")
                         << declarator
                         << QString(", ")
                         << static_cast<qint32>(type)
                         << QString(", ")
                         << QString(name.c_str())
                         << QString(", ")
                         << static_cast<qint32>(visibility)
                         << QString(");");
                qDebug() << QString("===> ") << declared;
            });
		}

		ClientController &ClientController::shared() {
			static ClientController clientController;

			return clientController;
		}

        template <typename Reply, typename Callable>
        void ClientController::registerReplyEvent(Callable const &callback)
        {
            m_clientCom->registerEvent(QString(Reply::EVENT().c_str()), 0, [this, &callback](void *data, unsigned int size) {
                Reply *reply = m_dataComFactory->getPackageFrom<Reply>(DataComEventFactory::DataComEvent{data, size}, m_commands.front());

                reply->command.apply([reply, &callback](auto &... args){
                    callback(args..., reply->get());
                });

                delete(reply);
                std::free(m_commands.front().data);
                m_commands.pop();
            });
        }

        template <typename Command, typename ... Args>
        void ClientController::sendCommand(Args const &... args)
        {
            DataComEventFactory::DataComEvent package = m_dataComFactory->createPackage<Command>(args...);

            m_clientCom->sendEvent(QString(Command::EVENT().c_str()), package.data, package.size);
            m_commands.push(package);
        }

        void ClientController::declaratorDeclare(EntityID declarator, ENTITY_CORE type, std::string const &name, VISIBILITYCORE visibility)
        {
            sendCommand<Command::Declarator::Declare>(declarator, type, name, visibility);
        }

        void ClientController::declaratorDeclared(std::function<void(EntityID, ENTITY_CORE, std::string const &, VISIBILITYCORE, EntityID)> const &callback)
        {
            registerReplyEvent<Reply::Declarator::Declared>(callback);
        }
	}
}
