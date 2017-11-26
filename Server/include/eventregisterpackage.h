#ifndef EVENTREGISTERPACKAGE_H
#define EVENTREGISTERPACKAGE_H

#include <QString>
#include "dulypack.h"
#include "headercommunication.h"

PACKED_STRUCT(EventRegisterPackage) {
    char eventName[256];
    unsigned int eventSize;
    char        enable;
};

PACKED_STRUCT(EventRegisterPackageAnswerServer) {
    char eventName[256];
    unsigned int id;
} ;

PACKED_STRUCT(SendEventRegisterPackageAnswerServer) {
    HeaderCommunication header;
    EventRegisterPackageAnswerServer eventRegister;
} ;

PACKED_STRUCT(SendEventRegisterPackage) {
    HeaderCommunication header;
    EventRegisterPackage eventRegister;
} ;

void createEventRegisterPackage(SendEventRegisterPackage &,
                                QString const &eventName,
                                unsigned int size,
                                bool enable);

void createEventRegisterPackageAnswerServer(SendEventRegisterPackageAnswerServer &,
                                QString const &eventName,
                                unsigned int id);

#endif // EVENTREGISTERPACKAGE_H
