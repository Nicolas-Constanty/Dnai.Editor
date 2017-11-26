#ifndef EVENTSENDPACKAGE_H
#define EVENTSENDPACKAGE_H

#include <QString>
#include "dulypack.h"
#include "headercommunication.h"

PACKED_STRUCT(EventSendPackage) {
    unsigned int eventId;
    /// + DATA [SIZE]
} ;

PACKED_STRUCT(EventSendFromClientPackage) {
    char    eventName[100];
    /// + DATA [SIZE]
} ;

PACKED_STRUCT(SendEventSendPackage) {
    HeaderCommunication header;
    EventSendPackage event;
} ;

PACKED_STRUCT(SendEventSendFromClientPackage) {
    HeaderCommunication header;
    EventSendFromClientPackage event;
} ;

SendEventSendPackage *createEventSendPackage(unsigned int id,
                            void *data, unsigned int size);

SendEventSendFromClientPackage *createEventSendFromClientPackage(QString const &,
                                void *data, unsigned int size);

#endif // EVENTSENDPACKAGE_H
