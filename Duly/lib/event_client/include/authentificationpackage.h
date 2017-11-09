#ifndef AUTHENTIFICATIONPACKAGE_H
#define AUTHENTIFICATIONPACKAGE_H

#include <QString>
#include "headercommunication.h"

typedef struct __attribute__((packed)) {
    char name[256];
} AuthentificationPackage;

typedef struct __attribute__((packed)) {
    HeaderCommunication header;
    AuthentificationPackage auth;
} SendAuthenticatePackage;

void createAuthenticatePackage(SendAuthenticatePackage &, QString const &name);

#endif // AUTHENTIFICATIONPACKAGE_H
