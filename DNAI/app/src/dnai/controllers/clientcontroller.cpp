#include "include/clientmanager.h"
#include "include/clientcommunication.h"
#include "include/dnai/controllers/clientcontroller.h"
#include "declarecorepackage.h"
#include "commands.h"
#include "replies.h"

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

			registerReplyEvent<Reply::EntityDeclared>("ENTITY_DECLARED", [](Reply::EntityDeclared const &reply) {

				qDebug() << "My amazing registered";

				Command::Declare::Data const &declare = reply.Field<Reply::COMMAND>();

				qDebug() << declare.Field<Command::Declare::NAME>().Data();
				qDebug() << declare.Field<Command::Declare::CONTAINER_ID>().Data();
				qDebug() << static_cast<qint32>(declare.Field<Command::Declare::ENTITY_TYPE>().Data());
				qDebug() << static_cast<qint32>(declare.Field<Command::Declare::VISIBILITY>().Data());
				qDebug() << static_cast<qint32>(reply.Field<Reply::RETURN>().Data());
			});
			/*
			m_clientCom->registerEvent("ENTITY_DECLARED",
			4,
			std::bind(&ClientController::onReceiveEntityDeclared,
			this, std::placeholders::_1, std::placeholders::_2));
			m_clientCom->registerEvent(DECLARE_EVENT_NAME,
			4,
			std::bind(&ClientController::onReceiveDeclare,
			this, std::placeholders::_1, std::placeholders::_2));
			*/
		}

		ClientController &ClientController::shared() {
			static ClientController clientController;

			return clientController;
		}

		void ClientController::onReceiveEntityDeclared(void *data, unsigned int size) {
			qDebug() << "ENTITY_DECLARED with size=" << size;
			Reply::EntityDeclared *entityDeclared = m_dataComFactory->getEntityDeclared(data, size); //(EntityDeclareCorePackage *)m_dataComFactory->serializeEntityDeclare(data, size);
			Command::Declare::Data const &declare = entityDeclared->Field<Reply::COMMAND>();

			qDebug() << declare.Field<Command::Declare::NAME>().Data();
			qDebug() << declare.Field<Command::Declare::CONTAINER_ID>().Data();
			qDebug() << (qint32)declare.Field<Command::Declare::ENTITY_TYPE>().Data();
			qDebug() << (qint32)declare.Field<Command::Declare::VISIBILITY>().Data();
			qDebug() << (qint32)entityDeclared->Field<Reply::RETURN>().Data();
		}

		void ClientController::onReceiveDeclare(void *data, unsigned int size) {
			DeclareCorePackage *declare = (DeclareCorePackage *)m_dataComFactory->serializeDeclare(data, size);

			qDebug() << declare->name;
			qDebug() << declare->containerID;
			qDebug() << (qint32)declare->entityType;
			qDebug() << (qint32)declare->visibility;

		}

		void ClientController::registerEvent(QString const &replyName, std::function<void(void *, unsigned int)> const &callback) const
		{
			m_clientCom->registerEvent(replyName, 0, callback);
		}

		// EVENT TO SEND
		void ClientController::sendDeclareEvent(PackageDataCom::ENTITYCORE entity_type,
			uint32_t containerID,
			QString const &name,
			PackageDataCom::VISIBILITYCORE visibility) {
			DataComEventFactory::DataComEvent data;

			data = m_dataComFactory->createDeclare(entity_type, containerID, name, visibility);
			m_clientCom->sendEvent(DECLARE_EVENT_NAME, data.data, data.size);
		}

		void ClientController::sendRemoveEvent(PackageDataCom::ENTITYCORE entity_type,
			uint32_t containerID,
			QString const &name) {
			DataComEventFactory::DataComEvent data;

			data = m_dataComFactory->createRemove(entity_type, containerID, name);
			m_clientCom->sendEvent(REMOVE_EVENT_NAME, data.data, data.size);
		}


		void ClientController::sendMoveEvent(PackageDataCom::ENTITYCORE entity_type,
			uint32_t fromID,
			uint32_t toID,
			QString const &name) {
			DataComEventFactory::DataComEvent data;

			data = m_dataComFactory->createMove(entity_type, fromID, toID, name);
			m_clientCom->sendEvent(MOVE_EVENT_NAME, data.data, data.size);

		}

		void ClientController::sendChangeVisibilityEvent(PackageDataCom::ENTITYCORE entity_type,
			uint32_t containerID,
			QString const &name,
			PackageDataCom::VISIBILITYCORE visibility) {
			DataComEventFactory::DataComEvent data;

			data = m_dataComFactory->createChangeVisibility(entity_type, containerID, name, visibility);
			m_clientCom->sendEvent(CHANGE_VISIBILITY_EVENT_NAME, data.data, data.size);
		}
	}
}