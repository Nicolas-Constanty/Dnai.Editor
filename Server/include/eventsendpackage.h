#ifndef EVENTSENDPACKAGE_H
#define EVENTSENDPACKAGE_H

#include <QString>
#include "pack.h"
#include "headercommunication.h"

PACKED(
struct EventSendPackage {
    unsigned int eventId;
    /// + DATA [SIZE]
}
);

PACKED(
struct EventSendFromClientPackage {
    char    eventName[100];
    /// + DATA [SIZE]
}
);

PACKED(
struct SendEventSendPackage{
    HeaderCommunication header;
    EventSendPackage event;
}
);

PACKED(
struct SendEventSendFromClientPackage {
    HeaderCommunication header;
    EventSendFromClientPackage event;
}
);

SendEventSendPackage *createEventSendPackage(unsigned int id,
                            void *data, unsigned int size);

SendEventSendFromClientPackage *createEventSendFromClientPackage(QString const &,
                                void *data, unsigned int size);

#endif // EVENTSENDPACKAGE_H
