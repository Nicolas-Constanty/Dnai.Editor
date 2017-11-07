#ifndef EVENTREGISTERPACKAGE_H
#define EVENTREGISTERPACKAGE_H

#include <QString>
#include "headercommunication.h"

typedef struct __attribute__((packed)) {
    char eventName[256];
    unsigned int eventSize;
    char        enable;
} EventRegisterPackage;

typedef struct __attribute__((packed)) {
    char eventName[256];
    unsigned int id;
} EventRegisterPackageAnswerServer;

typedef struct __attribute__((packed)) {
    HeaderCommunication header;
    EventRegisterPackageAnswerServer eventRegister;
} SendEventRegisterPackageAnswerServer;

typedef struct __attribute__((packed)) {
    HeaderCommunication header;
    EventRegisterPackage eventRegister;
} SendEventRegisterPackage;

void createEventRegisterPackage(SendEventRegisterPackage &,
                                QString const &eventName,
                                unsigned int size,
                                bool enable);

void createEventRegisterPackageAnswerServer(SendEventRegisterPackageAnswerServer &,
                                QString const &eventName,
                                unsigned int id);

#endif // EVENTREGISTERPACKAGE_H
