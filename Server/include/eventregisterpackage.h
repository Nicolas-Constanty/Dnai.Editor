#ifndef EVENTREGISTERPACKAGE_H
#define EVENTREGISTERPACKAGE_H

#include <QString>
#include "pack.h"
#include "headercommunication.h"

PACKED(
struct EventRegisterPackage {
    char eventName[256];
    unsigned int eventSize;
    char        enable;
}
);

PACKED(
struct EventRegisterPackageAnswerServer {
    char eventName[256];
    unsigned int id;
}
);

PACKED(
struct SendEventRegisterPackageAnswerServer {
    HeaderCommunication header;
    EventRegisterPackageAnswerServer eventRegister;
}
);

PACKED(
struct SendEventRegisterPackage {
    HeaderCommunication header;
    EventRegisterPackage eventRegister;
}
);

void createEventRegisterPackage(SendEventRegisterPackage &,
                                QString const &eventName,
                                unsigned int size,
                                bool enable);

void createEventRegisterPackageAnswerServer(SendEventRegisterPackageAnswerServer &,
                                QString const &eventName,
                                unsigned int id);

#endif // EVENTREGISTERPACKAGE_H
