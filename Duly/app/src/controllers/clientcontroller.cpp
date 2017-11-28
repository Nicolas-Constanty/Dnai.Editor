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
