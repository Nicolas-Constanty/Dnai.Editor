#ifndef CLIENTCONTROLLER_H_
# define CLIENTCONTROLLER_H_

#include <QHostAddress>
#include <QString>

class ClientCommunication;
class DataComEventFactory;

#include "core.pb.h"

#define CLIENT_NAME "DULY_GUI"

class ClientController {
private:
    ClientController();

public:
    static ClientController &shared();

public:
    void onReceiveEntityDeclared(void *, unsigned int);

public:
#define DECLARE_EVENT_NAME "DECLARE"
    void sendDeclareEvent(ENTITY entity_type,
                          uint32_t containerID,
                          QString const &name,
                          VISIBILITY visibility);

#define REMOVE_EVENT_NAME "REMOVE"
    void sendRemoveEvent(ENTITY entity_type,
                         uint32_t containerID,
                         QString const &name);


#define MOVE_EVENT_NAME "MOVE"
    void sendMoveEvent(ENTITY entity_type,
                       uint32_t fromID,
                       uint32_t toID,
                       QString const &name);

#define CHANGE_VISIBILITY_EVENT_NAME "CHANGE_VISIBILITY"
    void sendChangeVisibilityEvent(ENTITY entity_type,
                                   uint32_t containerID,
                                   QString const &name,
                                   VISIBILITY visibility);


private:
    ClientCommunication *m_clientCom;
    DataComEventFactory *m_dataComFactory;
    QString             m_name;
    quint16             m_port;
    QHostAddress        m_addr;
};

#endif
