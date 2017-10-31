#ifndef EVENTSENDPACKAGE_H
#define EVENTSENDPACKAGE_H

#include <QString>
#include "headercommunication.h"

typedef struct {
    unsigned int eventId;
    /// + DATA [SIZE]
} EventSendPackage;

typedef struct {
    char    eventName[100];
    /// + DATA [SIZE]
} EventSendFromClientPackage;

typedef struct {
    HeaderCommunication header;
    EventSendPackage event;
} SendEventSendPackage;

typedef struct {
    HeaderCommunication header;
    EventSendFromClientPackage event;
} SendEventSendFromClientPackage;

SendEventSendPackage *createEventSendPackage(unsigned int id,
                            void *data, unsigned int size);

SendEventSendFromClientPackage *createEventSendFromClientPackage(QString const &,
                                void *data, unsigned int size);

#endif // EVENTSENDPACKAGE_H
