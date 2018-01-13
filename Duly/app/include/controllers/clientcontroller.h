#ifndef CLIENTCONTROLLER_H_
# define CLIENTCONTROLLER_H_

#include <QHostAddress>
#include <QString>

class ClientCommunication;
class DataComEventFactory;

#include "packagecore.h"

#define CLIENT_NAME "DULY_GUI"

class ClientController {
private:
    ClientController();

public:
    static ClientController &shared();

public:
    void onReceiveEntityDeclared(void *, unsigned int);
    void onReceiveDeclare(void *, unsigned int);

public:
#define DECLARE_EVENT_NAME "DECLARE"
    void sendDeclareEvent(PackageDataCom::ENTITYCORE entity_type,
                          uint32_t containerID,
                          QString const &name,
                          PackageDataCom::VISIBILITYCORE visibility);

#define REMOVE_EVENT_NAME "REMOVE"
    void sendRemoveEvent(PackageDataCom::ENTITYCORE entity_type,
                         uint32_t containerID,
                         QString const &name);


#define MOVE_EVENT_NAME "MOVE"
    void sendMoveEvent(PackageDataCom::ENTITYCORE entity_type,
                       uint32_t fromID,
                       uint32_t toID,
                       QString const &name);

#define CHANGE_VISIBILITY_EVENT_NAME "CHANGE_VISIBILITY"
    void sendChangeVisibilityEvent(PackageDataCom::ENTITYCORE entity_type,
                                   uint32_t containerID,
                                   QString const &name,
                                   PackageDataCom::VISIBILITYCORE visibility);


private:
    ClientCommunication *m_clientCom;
    DataComEventFactory *m_dataComFactory;
    QString             m_name;
    quint16             m_port;
    QHostAddress        m_addr;
};

#endif
