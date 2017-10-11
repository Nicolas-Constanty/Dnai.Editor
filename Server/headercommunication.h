#ifndef HEADERCOMMUNICATION_H
#define HEADERCOMMUNICATION_H

typedef struct {
    int magicNumber;
    int packageSize;
    int id;
} HeaderCommunication;

#define CLIENT_AUTHENTIFICATION_ID 1
#define REGISTER_EVENT_ID 2
#define SEND_EVENT_ID 3

#endif // HEADERCOMMUNICATION_H
