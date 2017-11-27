#ifndef AUTHENTIFICATIONPACKAGE_H
#define AUTHENTIFICATIONPACKAGE_H

#include <QString>
#include "pack.h"
#include "headercommunication.h"

PACKED(
struct AuthentificationPackage {
    char name[256];
}
);

PACKED(
struct SendAuthenticatePackage {
    HeaderCommunication header;
    AuthentificationPackage auth;
}
);

void createAuthenticatePackage(SendAuthenticatePackage &, QString const &name);

#endif // AUTHENTIFICATIONPACKAGE_H
