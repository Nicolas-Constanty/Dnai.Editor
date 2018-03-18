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
#include "dnai/corepackages/replies/errorreply.h"

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

        private:
            template <typename Command>
            const Command *popLastCommand()
            {
                typename CommandsMap::iterator it = m_commands.find(Command::EVENT());

                if (it == m_commands.end()) return nullptr;

                const Command *toret = dynamic_cast<const Command *>(it->second.front());

                if (toret != nullptr)
                    it->second.pop();
                return toret;
            }

        private:
            template <typename Reply, typename Cb>
            void registerOnReply(Cb const &callback)
            {
                m_clientCom->registerEvent(Reply::EVENT().c_str(), 0, [this, &callback](void *data, unsigned int size) {
                    const Reply::Command *cmd = popLastCommand<Reply::Command>();

                    if (cmd == nullptr)
                    {
                        qDebug() << "Receiving " << Reply::EVENT().c_str() << " but there was no command " << Reply::Command::EVENT().c_str() << " done";
                        return;
                    }

                    Reply reply(*cmd);

                    if (size > 0)
                    {
                        Cerealization::Cerealizer::BinaryStream stream((Cerealization::Cerealizer::BinaryStream::Byte *)data, size);

                        reply.fillFrom(stream);
                    }
                    callback(std::cref(reply));
                });
            }

        public:
            template <typename Reply, typename Callable, typename Error>
            void registerReplyEvent(Callable const &callback, Error const &error)
            {
                registerOnReply<Reply>(callback);
                registerOnReply<corepackages::ErrorReply<Reply::Command>>(error);
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
            }

		private:
            ClientCommunication * m_clientCom;
			QString             m_name;
			quint16             m_port;
			QHostAddress        m_addr;

            //commands queue
        private:
            CommandsMap  m_commands;
		};      
	}
}

#endif
