#ifndef CLIENTCONTROLLER_H_
# define CLIENTCONTROLLER_H_

#include <unordered_map>
#include <functional>
#include <queue>

#include <QHostAddress>
#include <QString>

#include "include/clientcommunication.h"
#include "Cerealizer/Binary/Binary.hpp"
#include "dnai/corepackages/coreserialoperations.h"
#include "dnai/corepackages/commands/icommanddata.h"
#include "dnai/enums/core/core.h"

namespace dnai
{
	namespace controllers
	{
#define CLIENT_NAME "DNAI_GUI"

        class ClientController
        {
        private:
            using Command = corepackages::ICommandData;
            using CommandsQueue = std::queue<const Command *>;
            using CommandsMap = std::unordered_map<std::string, CommandsQueue>;

		private:
			ClientController();

		public:
			static qint16 serverPort;
			static ClientController &shared();

        public:
            template <typename Reply, typename Callable>
            void registerReplyEvent(Callable const &callback)
            {
                m_clientCom->registerEvent(Reply::EVENT().c_str(), 0, [this, &callback](void *data, unsigned int size) {
                    typename CommandsMap::iterator it = m_commands.find(Reply::Command::EVENT());

                    if (it == m_commands.end())
                    {
                        qDebug() << "Receiving an event " << Reply::EVENT().c_str() << " but there was no command " << Reply::Command::EVENT().c_str() << " done";
                        return;
                    }

                    const Reply::Command *cmd = dynamic_cast<const Reply::Command *>(it->second.front());
                    Reply reply(*cmd);

                    if (size > 0)
                    {
                        Cerealization::Cerealizer::BinaryStream stream((Cerealization::Cerealizer::BinaryStream::Byte *)data, size);

                        reply.fillFrom(stream);
                    }
                    callback(std::cref(reply));
                    it->second.pop();
                });
            }

            template <typename Cmd>
            void sendCommand(Cmd &tosend)
            {
                Cerealization::Cerealizer::BinaryStream stream;
                Cerealization::Cerealizer::JSONStream js;

                js << tosend;

                qDebug() << "Sending data for event: " << Cmd::EVENT().c_str() << " => " << js.Data().c_str();
                stream << tosend;
                m_clientCom->sendEvent(Cmd::EVENT().c_str(), stream.Data(), stream.Size());
                m_commands[Cmd::EVENT()].emplace(&tosend);
                m_eventQueue.push(Cmd::EVENT());
            }

		private:
            ClientCommunication * m_clientCom;
			QString             m_name;
			quint16             m_port;
			QHostAddress        m_addr;

            //commands queue
        private:
            CommandsMap  m_commands;
            std::queue<std::string> m_eventQueue;
		};      
	}
}

#endif
