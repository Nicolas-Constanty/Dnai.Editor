#include "authentificationpackage.h"
#include "eventregisterpackage.h"
#include "eventsendpackage.h"

void createAuthenticatePackage(SendAuthenticatePackage &data,
                               QString const &name) {
    data.header.magicNumber = MAGIC_NUMBER;
    data.header.id = CLIENT_AUTHENTIFICATION_ID;
    data.header.packageSize = sizeof(data.auth);

    memset(data.auth.name, 0, sizeof(data.auth.name));
    memcpy(data.auth.name, name.toStdString().c_str(), name.size());
}

void createEventRegisterPackage(SendEventRegisterPackage &data,
                                QString const &eventName,
                                unsigned int size,
                                bool enable) {
    data.header.magicNumber = MAGIC_NUMBER;
    data.header.id = REGISTER_EVENT_ID;
    data.header.packageSize = sizeof(data.eventRegister);

    memset(data.eventRegister.eventName, 0, sizeof(data.eventRegister.eventName));
    memcpy(data.eventRegister.eventName, eventName.toStdString().c_str(), eventName.size());
    data.eventRegister.eventSize = size;
    data.eventRegister.enable = enable ? 1 : 0;
}

void createEventRegisterPackageAnswerServer(SendEventRegisterPackageAnswerServer &data,
                                QString const &eventName,
                                unsigned int id) {
    data.header.magicNumber = MAGIC_NUMBER;
    data.header.id = REGISTER_EVENT_ID;
    data.header.packageSize = sizeof(data.eventRegister);

    memset(data.eventRegister.eventName, 0, sizeof(data.eventRegister.eventName));
    memcpy(data.eventRegister.eventName, eventName.toStdString().c_str(), eventName.size());

    data.eventRegister.id = id;
}

SendEventSendPackage *createEventSendPackage(unsigned int id, void *data, unsigned int size) {
    SendEventSendPackage *info = (SendEventSendPackage *)malloc(sizeof(SendEventSendPackage) + size);
    void *dataCursor = (void *)(((char *)info) + sizeof(SendEventSendPackage));

    info->header.magicNumber = MAGIC_NUMBER;
    info->header.id = SEND_EVENT_ID;
    info->header.packageSize = sizeof(info->event) + size;
    info->event.eventId = id;

    memcpy(dataCursor, data, size);

    return (info);

}


SendEventSendFromClientPackage *createEventSendFromClientPackage(QString const &name,
                                void *data, unsigned int size) {
    SendEventSendFromClientPackage *info = (SendEventSendFromClientPackage *)malloc(sizeof(SendEventSendFromClientPackage) + size);
    void *dataCursor = (void *)(((char *)info) + sizeof(SendEventSendFromClientPackage));

    info->header.magicNumber = MAGIC_NUMBER;
    info->header.id = SEND_EVENT_ID;
    info->header.packageSize = sizeof(info->event) + size;

    memset(info->event.eventName, 0, sizeof(info->event.eventName));
    memcpy(info->event.eventName, name.toStdString().c_str(), name.size());
    //info->event.eventId = id;

    memcpy(dataCursor, data, size);

    return (info);
}




