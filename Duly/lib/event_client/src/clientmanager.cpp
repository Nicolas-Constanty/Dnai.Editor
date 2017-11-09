#include "clientmanager.h"

ClientManager &ClientManager::shared() {
    static ClientManager manager;
    return manager;
}

ClientCommunication *ClientManager::newClient(QHostAddress addr, quint16 port, QString const &name) {
    ClientCommunication *client = new ClientCommunication(addr, port, name);

    client->start();
    m_clients[name] = client;
    return (client);
}

ClientCommunication *ClientManager::getFrom(QString const &name) const {
    QMap<QString, ClientCommunication *>::const_iterator it = m_clients.find(name);
    if (it == m_clients.end()) {
        return (NULL);
    }
    return (it.value());
}
