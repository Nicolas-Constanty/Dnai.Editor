#ifndef AUTHENTIFICATIONPACKAGE_H
#define AUTHENTIFICATIONPACKAGE_H

#include <QString>
#include "headercommunication.h"

typedef struct {
    char name[256];
} AuthentificationPackage;

typedef struct {
    HeaderCommunication header;
    AuthentificationPackage auth;
} SendAuthenticatePackage;

void createAuthenticatePackage(SendAuthenticatePackage &, QString const &name);

#endif // AUTHENTIFICATIONPACKAGE_H
