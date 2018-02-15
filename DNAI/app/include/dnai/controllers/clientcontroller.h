#ifndef CLIENTCONTROLLER_H_
# define CLIENTCONTROLLER_H_

#include <functional>

#include <QHostAddress>
#include <QString>

class ClientCommunication;

#include "datacomeventfactory.h"

#include "packagecore.h"

namespace dnai
{
	namespace controllers
	{
#define CLIENT_NAME "DULY_GUI"

		class ClientController {
		private:
			ClientController();

		public:
			static qint16 serverPort;
			static ClientController &shared();

		public:
			void onReceiveEntityDeclared(void *, unsigned int);
			void onReceiveDeclare(void *, unsigned int);

		private:
			void registerEvent(QString const &replyName, std::function<void(void *, unsigned int)> const &callback) const;

		public:
			template <typename Reply, typename Callable>
			void registerReplyEvent(QString const &replyName, Callable const &callback) const
			{
				registerEvent(replyName, [this, &callback](void *data, unsigned int size) {
					Reply *reply = m_dataComFactory->DeserializeReplyFrom<Reply>(data, size);

					callback(std::cref<Reply>(*reply));

					delete(reply);
				});
			}

		public:
#define DECLARE_EVENT_NAME "DECLARE"
			void sendDeclareEvent(PackageDataCom::ENTITYCORE entity_type,
				uint32_t containerID,
				QString const &name,
				PackageDataCom::VISIBILITYCORE visibility);

#define REMOVE_EVENT_NAME "REMOVE"
			void sendRemoveEvent(PackageDataCom::ENTITYCORE entity_type,
				uint32_t containerID,
				QString const &name);


#define MOVE_EVENT_NAME "MOVE"
			void sendMoveEvent(PackageDataCom::ENTITYCORE entity_type,
				uint32_t fromID,
				uint32_t toID,
				QString const &name);

#define CHANGE_VISIBILITY_EVENT_NAME "CHANGE_VISIBILITY"
			void sendChangeVisibilityEvent(PackageDataCom::ENTITYCORE entity_type,
				uint32_t containerID,
				QString const &name,
				PackageDataCom::VISIBILITYCORE visibility);


		private:
			ClientCommunication * m_clientCom;
			DataComEventFactory *m_dataComFactory;
			QString             m_name;
			quint16             m_port;
			QHostAddress        m_addr;
		};
	}
}

#endif