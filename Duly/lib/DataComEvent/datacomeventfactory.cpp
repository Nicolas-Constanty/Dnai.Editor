#include <QDebug>
#include <QString>
#include "datacomeventfactory.h"

DataComEventFactory::DataComEventFactory()
{

}

DataComEventFactory::DataComEvent DataComEventFactory::createDataComEvent(google::protobuf::Message &message) {
    DataComEventFactory::DataComEvent dataCom;
    dataCom.size = message.ByteSize();
    dataCom.data = (void *)malloc(dataCom.size);

    if (!message.SerializeToArray(dataCom.data, dataCom.size)) {
        dataCom.size = 0;
        free(dataCom.data);
        dataCom.data = malloc(0);
    }
    return (dataCom);
}

DataComEventFactory::DataComEvent DataComEventFactory::createDeclare(ENTITY entity_type,
                                                 uint32_t containerID,
                                                 QString const &name,
                                                 VISIBILITY visibility) {
    Declare declare;

     declare.set_entitytype(entity_type);
     declare.set_containerid(containerID);
     declare.set_name(name.toStdString().c_str());
     declare.set_visibility(visibility);

     return (createDataComEvent(declare));
}

DataComEventFactory::DataComEvent DataComEventFactory::createRemove(ENTITY entity_type,
                                                                    uint32_t containerID,
                                                                    QString const &name) {
    Remove remove;

    remove.set_entitytype(entity_type);
    remove.set_containerid(containerID);
    remove.set_name(name.toStdString().c_str());

    return (createDataComEvent(remove));
}


DataComEventFactory::DataComEvent DataComEventFactory::createMove(ENTITY entity_type,
                       uint32_t fromID,
                       uint32_t toID,
                       QString const &name) {
    Move move;

    move.set_entitytype(entity_type);
    move.set_fromid(fromID);
    move.set_toid(toID);
    move.set_name(name.toStdString().c_str());

    return (createDataComEvent(move));
}

DataComEventFactory::DataComEvent DataComEventFactory::createChangeVisibility(ENTITY entity_type,
                                    uint32_t containerID,
                                    QString const &name,
                                    VISIBILITY visibility) {
    ChangeVisibility changeVisibility;

    changeVisibility.set_entitytype(entity_type);
    changeVisibility.set_containerid(containerID);
    changeVisibility.set_name(name.toStdString().c_str());
    changeVisibility.set_newvisi(visibility);

    return (createDataComEvent(changeVisibility));
}
