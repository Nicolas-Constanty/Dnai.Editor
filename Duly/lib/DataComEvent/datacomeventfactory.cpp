#include <QDebug>
#include <QString>
#include "datacomeventfactory.h"
#include "declarecorepackage.h"
#include "commands.h"

DataComEventFactory::DataComEventFactory()
{

}

/*DataComEventFactory::DataComEvent DataComEventFactory::createDataComEvent(google::protobuf::Message &message) {
    DataComEventFactory::DataComEvent dataCom;
    dataCom.size = message.ByteSize();
    dataCom.data = (void *)malloc(dataCom.size);

    if (!message.SerializeToArray(dataCom.data, dataCom.size)) {
        dataCom.size = 0;
        free(dataCom.data);
        dataCom.data = malloc(0);
    }
    return (dataCom);
}*/

DataComEventFactory::DataComEvent DataComEventFactory::createDataComEvent(qint32 size) {
    DataComEventFactory::DataComEvent dataCom;
    dataCom.size = size;
    dataCom.data = (void *)malloc(dataCom.size);

    if (dataCom.data == NULL) {
        dataCom.size = 0;
      //  free(dataCom.data);
        dataCom.data = malloc(0);
    }
    return (dataCom);
}

void DataComEventFactory::memcpyDataCom(void **dest, void *src, size_t size) {
    memcpy(*dest, src, size);
    (*dest) = static_cast<char*>(*dest) + size;
}

void DataComEventFactory::memcpySerializeDataCom(void *dest, void **src, size_t size) {
    memcpy(dest, *src, size);
    (*src) = static_cast<char*>(*src) + size;
}

DataComEventFactory::DataComEvent DataComEventFactory::createDeclare(PackageDataCom::ENTITYCORE entity_type,
                                                 uint32_t containerID,
                                                 QString const &name,
                                                 PackageDataCom::VISIBILITYCORE visibility) {

    return SerializeCommandToDataComEvent<Command::Declare>(entity_type, containerID, name, visibility);
}

void *DataComEventFactory::serializeDeclare(void *data, unsigned int size) {
    DeclareCorePackage *declare = new DeclareCorePackage();
    qint32 sizeName = 0;

    memcpySerializeDataCom(&(declare->entityType), &data, sizeof(declare->entityType));
    memcpySerializeDataCom(&(declare->containerID), &data, sizeof(declare->containerID));
    memcpySerializeDataCom(&sizeName, &data, sizeof(sizeName));

    char *name = (char *)malloc(sizeName + 1);
    memcpySerializeDataCom((void *)name, &data, sizeName);
    name[sizeName] = '\0';
    declare->name = QString(name);

    free(name);

    memcpySerializeDataCom(&(declare->visibility), &data, sizeof(declare->visibility));

    return declare;
}

void *DataComEventFactory::serializeEntityDeclare(void *data, unsigned int size) {
    EntityDeclareCorePackage *declare = new EntityDeclareCorePackage();
    qint32 sizeName = 0;

    memcpySerializeDataCom(&(declare->entityType), &data, sizeof(declare->entityType));
    memcpySerializeDataCom(&(declare->containerID), &data, sizeof(declare->containerID));
    memcpySerializeDataCom(&sizeName, &data, sizeof(sizeName));

    char *name = (char *)malloc(sizeName + 1);
    memcpySerializeDataCom((void *)name, &data, sizeName);
    name[sizeName] = '\0';
    declare->name = QString(name);

    free(name);

    memcpySerializeDataCom(&(declare->visibility), &data, sizeof(declare->visibility));
    memcpySerializeDataCom(&(declare->id), &data, sizeof(declare->id));

    return declare;
}

DataComEventFactory::DataComEvent DataComEventFactory::createRemove(PackageDataCom::ENTITYCORE entity_type,
                                                                    uint32_t containerID,
                                                                    QString const &name) {
  /*  Remove remove;

    remove.set_entitytype(entity_type);
    remove.set_containerid(containerID);
    remove.set_name(name.toStdString().c_str());*/

    return (createDataComEvent(4));
}


DataComEventFactory::DataComEvent DataComEventFactory::createMove(PackageDataCom::ENTITYCORE entity_type,
                       uint32_t fromID,
                       uint32_t toID,
                       QString const &name) {
 /*   Move move;

    move.set_entitytype(entity_type);
    move.set_fromid(fromID);
    move.set_toid(toID);
    move.set_name(name.toStdString().c_str());*/

    return (createDataComEvent(3));
}

DataComEventFactory::DataComEvent DataComEventFactory::createChangeVisibility(PackageDataCom::ENTITYCORE entity_type,
                                    uint32_t containerID,
                                    QString const &name,
                                    PackageDataCom::VISIBILITYCORE visibility) {
   /* ChangeVisibility changeVisibility;

    changeVisibility.set_entitytype(entity_type);
    changeVisibility.set_containerid(containerID);
    changeVisibility.set_name(name.toStdString().c_str());
    changeVisibility.set_newvisi(visibility);*/

    return (createDataComEvent(2));
}
