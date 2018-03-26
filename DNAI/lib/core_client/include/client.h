#ifndef CLIENTCONTROLLER_H_
# define CLIENTCONTROLLER_H_

#include <unordered_map>
#include <functional>
#include <queue>

#include <QHostAddress>
#include <QString>

#include "Cerealizable/Tuple.hpp"
#include "Cerealizer/Binary/Binary.hpp"
#include "serialoperations.h"

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
        template <typename ... Args>
        void callCommand(QString const &name, Args &... args) const
        {
            Cerealization::Cerealizable::Tuple<Args...> toserialize(args...);
            Cerealization::Cerealizer::BinaryStream stream;

            stream << toserialize;
            m_clientCom->sendEvent(name, stream.Data(), static_cast<unsigned int>(stream.Size()));
        }

        template <typename ... Args>
        void registerReply(QString const &event, std::function<void(Args ...)> const &then) const
        {
            m_clientCom->registerEvent(event, 0, [&then](void *data, unsigned int size) {
                Cerealization::Cerealizable::Tuple<Args...> toInject;
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
