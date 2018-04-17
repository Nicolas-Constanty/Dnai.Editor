#ifndef CLIENTCONTROLLER_H_
# define CLIENTCONTROLLER_H_

#include <unordered_map>
#include <functional>
#include <queue>

#include <QHostAddress>
#include <QString>

#include "serialoperations.h"
#include "Cerealizer/Binary/Binary.hpp"

#include "clientcommunication.h"

#include "core.h"

class ClientCommunication;

namespace core
{
    class Client
    {
    private:
        Client();

    public:
        static qint16 serverPort;
        static QString clientName;
        static Client &shared();

    public:
        void callCommand(QString const &name) const
        {
            m_clientCom->sendEvent(name, nullptr, 0);
        }

        template <typename First, typename ... Args>
        void callCommand(QString const &name, First const &first, Args const &... args) const
        {
            Cerealization::Cerealizable::Tuple<First, Args...> toserialize(first, args...);
            Cerealization::Cerealizer::BinaryStream stream;

            stream << toserialize;
            m_clientCom->sendEvent(name, stream.Data(), static_cast<unsigned int>(stream.Size()));
        }

        void registerReply(QString const &event, std::function<void()> const &then) const
        {
            m_clientCom->registerEvent(event, 0, [then](void *, unsigned int) { then(); });
        }

        template <typename First, typename ... Args>
        void registerReply(QString const &event, std::function<void(First, Args ...)> const &then) const
        {
            m_clientCom->registerEvent(event, 0, [then](void *data, unsigned int size) {
                Cerealization::Cerealizable::Tuple<First, Args ...> toInject;
                Cerealization::Cerealizer::BinaryStream stream((Cerealization::Cerealizer::BinaryStream::Byte *)data, size);

                stream >> toInject;

                toInject.apply(then);
            });
        }

    private:
        ClientCommunication *m_clientCom;
        QString             m_name;
        quint16             m_port;
        QHostAddress        m_addr;
    };
}

#endif
