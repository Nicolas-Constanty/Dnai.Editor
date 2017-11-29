#include "datacomeventfactory.h"
#include "include/clientmanager.h"
#include "include/clientcommunication.h"
#include "include/controllers/clientcontroller.h"

ClientController::ClientController()
    : m_clientCom(NULL),
      m_dataComFactory(new DataComEventFactory()),
      m_name(CLIENT_NAME),
      m_port(7777),
      m_addr(QHostAddress::LocalHost)
{
    m_clientCom = ClientManager::shared().newClient(m_addr,
                                                    m_port,
                                                    m_name);
}

ClientController &ClientController::shared() {
    static ClientController clientController;

    return clientController;
}

// EVENT TO SEND

void ClientController::sendDeclareEvent(ENTITY entity_type,
                      uint32_t containerID,
                      QString const &name,
                      VISIBILITY visibility) {
    DataComEventFactory::DataComEvent data;

    data = m_dataComFactory->createDeclare(entity_type, containerID, name, visibility);
    m_clientCom->sendEvent(DECLARE_EVENT_NAME, data.data, data.size);
}

void ClientController::sendRemoveEvent(ENTITY entity_type,
                                       uint32_t containerID,
                                       QString const &name) {
    DataComEventFactory::DataComEvent data;

    data = m_dataComFactory->createRemove(entity_type, containerID, name);
    m_clientCom->sendEvent(REMOVE_EVENT_NAME, data.data, data.size);
}


void ClientController::sendMoveEvent(ENTITY entity_type,
                       uint32_t fromID,
                       uint32_t toID,
                       QString const &name) {
    DataComEventFactory::DataComEvent data;

    data = m_dataComFactory->createMove(entity_type, fromID, toID, name);
    m_clientCom->sendEvent(MOVE_EVENT_NAME, data.data, data.size);

}

void ClientController::sendChangeVisibilityEvent(ENTITY entity_type,
                                    uint32_t containerID,
                                    QString const &name,
                                    VISIBILITY visibility) {
    DataComEventFactory::DataComEvent data;

    data = m_dataComFactory->createChangeVisibility(entity_type, containerID, name, visibility);
    m_clientCom->sendEvent(CHANGE_VISIBILITY_EVENT_NAME, data.data, data.size);
}
