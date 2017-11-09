#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <QString>
#include <QMap>
#include "clientcommunication.h"

class Q_DECL_EXPORT ClientManager {

public:
    static ClientManager &shared();

public:
    ClientCommunication *newClient(QHostAddress addr, quint16 port, QString const &name);
    ClientCommunication *getFrom(QString const &name) const;

private:
    QMap<QString, ClientCommunication *> m_clients;
};

#endif // CLIENTMANAGER_H
