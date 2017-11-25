#ifndef DATACOMEVENTFACTORY_H
#define DATACOMEVENTFACTORY_H

#include "core.pb.h"
#include <QObject>

class Q_DECL_EXPORT DataComEventFactory
{
public:
    typedef struct DataComEvent {
      public:
        void *data;
        unsigned int size;
        DataComEvent() {
            data = NULL;
            size = 0;
        }

        DataComEvent(DataComEvent const &other) {
            *this = other;
        }

        DataComEvent &operator=(DataComEvent const &other) {
            this->data = other.data;
            this->size = other.size;
            return (*this);
        }

    } DataComEvent;

public:
    DataComEventFactory();

    DataComEvent createDeclare(ENTITY entity_type,
                       uint32_t containerID,
                       QString const &name,
                       VISIBILITY visibility);
};

#endif // DATACOMEVENTCONTROLLER_H
