#ifndef HEADERCOMMUNICATION_H
#define HEADERCOMMUNICATION_H

typedef struct __attribute__((packed)) {
    int magicNumber;
    unsigned int packageSize;
    unsigned int id;
} HeaderCommunication;

#define MAGIC_NUMBER 0x44756c79

#define CLIENT_AUTHENTIFICATION_ID 1
#define REGISTER_EVENT_ID 2
#define SEND_EVENT_ID 3

#endif // HEADERCOMMUNICATION_H
