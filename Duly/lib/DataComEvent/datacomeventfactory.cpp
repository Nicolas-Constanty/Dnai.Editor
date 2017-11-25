#include <QDebug>
#include <QString>
#include "datacomeventfactory.h"

DataComEventFactory::DataComEventFactory()
{

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

     DataComEventFactory::DataComEvent dataCom;// = new DataComEventFactory::DataComEvent();
     dataCom.size = declare.ByteSize();
     dataCom.data = (void *)malloc(dataCom.size);

     if (!declare.SerializeToArray(dataCom.data, dataCom.size)) {
       //  Declare secondDeclare;
       //  secondDeclare.ParseFromArray(array, sizeof(array));
       //  qDebug() << QString(secondDeclare.name().c_str());
         qDebug() << "[FAILED]";
         qDebug() << "entity_type: " << entity_type;
         qDebug() << "containerID: " << containerID;
         qDebug() << "name: " << name;
         qDebug() << "visibility: " << visibility;
         dataCom.size = 0;
         free(dataCom.data);
         dataCom.data = malloc(0);
     }
     return (dataCom);
}
