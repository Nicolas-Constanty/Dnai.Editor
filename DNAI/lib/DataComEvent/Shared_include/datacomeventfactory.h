#ifndef DATACOMEVENTFACTORY_H
#define DATACOMEVENTFACTORY_H

#include <QObject>
#include <QDebug>

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

private:
    template <typename Command>
    DataComEvent createPackageFrom(Command &cmd);

public:
    template <typename Package, typename ... Args>
    DataComEvent createPackage(Args const &... args)
    {
        Package pck(args...);
        return createPackageFrom(pck);
    }

    template <typename Reply>
    Reply *getPackageFrom(DataComEvent reply, DataComEvent command);
};

#endif // DATACOMEVENTCONTROLLER_H
