#ifndef DATACOMEVENTFACTORY_H
#define DATACOMEVENTFACTORY_H

//#include "core.pb.h"
#include <QObject>
#include "packagecore.h"


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

private:
  //  DataComEvent createDataComEvent(google::protobuf::Message &);
    DataComEvent createDataComEvent(qint32 size);
    void memcpyDataCom(void **dest, void *src, size_t);
    void memcpySerializeDataCom(void *dest, void **src, size_t);

public:
    DataComEventFactory();

    DataComEvent createDeclare(PackageDataCom::ENTITYCORE entity_type,
                       uint32_t containerID,
                       QString const &name,
                       PackageDataCom::VISIBILITYCORE visibility);
    void *serializeDeclare(void *, unsigned int size);
    void *serializeEntityDeclare(void *, unsigned int size);

    DataComEvent createRemove(PackageDataCom::ENTITYCORE entity_type,
                              uint32_t containerID,
                              QString const &name);

    DataComEvent createMove(PackageDataCom::ENTITYCORE entity_type,
                           uint32_t fromID,
                           uint32_t toID,
                           QString const &name);

    DataComEvent createChangeVisibility(PackageDataCom::ENTITYCORE entity_type,
                                        uint32_t containerID,
                                        QString const &name,
                                        PackageDataCom::VISIBILITYCORE visibility);

};

#endif // DATACOMEVENTCONTROLLER_H
