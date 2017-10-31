#ifndef EVENTREGISTERPACKAGE_H
#define EVENTREGISTERPACKAGE_H

#include <QString>
#include "headercommunication.h"

typedef struct {
    char eventName[256];
    unsigned int eventSize;
    char        enable;
} EventRegisterPackage;

typedef struct {
    char eventName[256];
    unsigned int id;
} EventRegisterPackageAnswerServer;

typedef struct {
    HeaderCommunication header;
    EventRegisterPackageAnswerServer eventRegister;
} SendEventRegisterPackageAnswerServer;

typedef struct {
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
