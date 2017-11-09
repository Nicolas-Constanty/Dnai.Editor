#ifndef EVENTSENDPACKAGE_H
#define EVENTSENDPACKAGE_H

#include <QString>
#include "headercommunication.h"

typedef struct __attribute__((packed)) {
    unsigned int eventId;
    /// + DATA [SIZE]
} EventSendPackage;

typedef struct __attribute__((packed)) {
    char    eventName[100];
    /// + DATA [SIZE]
} EventSendFromClientPackage;

typedef struct __attribute__((packed)) {
    HeaderCommunication header;
    EventSendPackage event;
} SendEventSendPackage;

typedef struct __attribute__((packed)) {
    HeaderCommunication header;
    EventSendFromClientPackage event;
} SendEventSendFromClientPackage;

SendEventSendPackage *createEventSendPackage(unsigned int id,
                            void *data, unsigned int size);

SendEventSendFromClientPackage *createEventSendFromClientPackage(QString const &,
                                void *data, unsigned int size);

#endif // EVENTSENDPACKAGE_H
