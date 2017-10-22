#ifndef EVENTREGISTERPACKAGE_H
#define EVENTREGISTERPACKAGE_H

typedef struct {
    char eventName[256];
    unsigned int eventSize;
    char        enable;
} EventRegisterPackage;

typedef struct {
    char eventName[256];
    unsigned int eventSize;
} EventRegisterPackageAnswerServer;

#endif // EVENTREGISTERPACKAGE_H
