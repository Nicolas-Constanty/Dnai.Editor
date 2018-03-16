#ifndef CLIENTCONTROLLER_H_
# define CLIENTCONTROLLER_H_

#include <functional>
#include <queue>

#include <QHostAddress>
#include <QString>

#include "datacomeventfactory.h"
#include "packagecore.h"

class ClientCommunication;

using namespace PackageDataCom;

namespace dnai
{
	namespace controllers
	{
#define CLIENT_NAME "DNAI_GUI"

		class ClientController {
		private:
			ClientController();

		public:
			static qint16 serverPort;
			static ClientController &shared();

		private:
            template <typename Reply, typename Callable>
            void registerReplyEvent(Callable const &callback);

        private:
            template <typename Command, typename ... Args>
            void sendCommand(Args const &... args);

		public:
            void declaratorDeclare(EntityID declarator, ENTITY_CORE type, std::string const &name, VISIBILITYCORE visibility);

        public:
            void declaratorDeclared(std::function<void(EntityID, ENTITY_CORE, std::string const &, VISIBILITYCORE, EntityID)> const &callback);

		private:
			ClientCommunication * m_clientCom;
			DataComEventFactory *m_dataComFactory;
			QString             m_name;
			quint16             m_port;
			QHostAddress        m_addr;

            //commands queue
        private:
            std::queue<DataComEventFactory::DataComEvent>  m_commands;
		};
	}
}

#endif
