#ifndef DATACOMEVENTFACTORY_H
#define DATACOMEVENTFACTORY_H

#include <QObject>
#include <QDebug>

#include "commands/commands.h"
#include "replies/replies.h"
#include "packagecore.h"
#include "coreserialoperations.h"

class Q_DECL_EXPORT DataComEventFactory
{
public:
    class DataComEvent
    {
	public:
		void *data;
		unsigned int size;

        DataComEvent(void *data = nullptr, unsigned int size = 0):
            data{data},
            size{size}
        {

		}

        DataComEvent(DataComEvent const &other) {
			*this = other;
		}

		DataComEvent &operator=(DataComEvent const &other) {
			this->data = other.data;
			this->size = other.size;
			return (*this);
		}
    };

public:
    DataComEventFactory() = default;
    ~DataComEventFactory() = default;

public:
    template <typename Package, typename ... Args>
    DataComEvent createPackage(Args const &... args)
    {
        Package pck(args...);
        Cerealization::Cerealizer::BinaryStream stream;

        stream << pck;

        return DataComEvent{
            memcpy(std::malloc(stream.Size()), stream.Data(), stream.Size()),
            static_cast<unsigned int>(stream.Size())
        };
    }

    template <typename Reply>
    Reply *getPackageFrom(DataComEvent reply, DataComEvent command)
    {
        std::unique_ptr<Reply> package(new Reply());
        Cerealization::Cerealizer::BinaryStream replyStream((Cerealization::Cerealizer::BinaryStream::Byte *)reply.data, reply.size);
        Cerealization::Cerealizer::BinaryStream commandStream((Cerealization::Cerealizer::BinaryStream::Byte *)command.data, command.size);

        replyStream >> *package;
        commandStream >> package->command;

        return package.release();
    }
};

#endif // DATACOMEVENTCONTROLLER_H
