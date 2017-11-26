#ifndef AUTHENTIFICATIONPACKAGE_H
#define AUTHENTIFICATIONPACKAGE_H

#include <QString>
#include "dulypack.h"
#include "headercommunication.h"

PACKED_STRUCT(AuthentificationPackage) {
    char name[256];
};

PACKED_STRUCT(SendAuthenticatePackage) {
    HeaderCommunication header;
    AuthentificationPackage auth;
};

void createAuthenticatePackage(SendAuthenticatePackage &, QString const &name);

#endif // AUTHENTIFICATIONPACKAGE_H
