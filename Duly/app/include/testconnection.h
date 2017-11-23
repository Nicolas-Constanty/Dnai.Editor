#ifndef TESTCONNECTION_H
#define TESTCONNECTION_H

#include <QDebug>
#include <QObject>
#include "include/clientcommunication.h"

class TestConnection : public QObject {
    Q_OBJECT

public:
    TestConnection(ClientCommunication &com) : m_com(com) {

    }
    typedef struct __attribute__((packed))  {
        long a;
        long b;
        char c[100];
    } POPO;

    typedef struct __attribute__((packed)) {
        float a;
        double b;
        short c;
        long d;
        char l;
    } POPI;


public slots:


    void update() {
       /* POPO toto;
        toto.a = 123;
        toto.b = 1;
        memset(toto.c, 0, sizeof(toto.c));
        memcpy(toto.c, "YOLOLOLOLO", sizeof("YOLOLOLOLO"));
        m_com.sendEvent("KOALA", &toto, sizeof(POPO));*/
        static int u = 0;
        if (u % 2 == 0) {
            qDebug() << "SEND 4";
            int u = 1234;
            m_com.sendEvent("POPOLE", &u, 4);
        } else {
            qDebug() << "SEND 1";
            char u = 'A';
            m_com.sendEvent("POPOLE", &u, 1);
        }
        ++u;
    }

    void updateTITI() {
   //     int a = 33;
        char c = 'K';
        m_com.sendEvent("TITI", &c, 1);
    }

    void updateTOTO() {
        POPI toto;
        toto.a = 3.14000000;
        toto.b = 5.3212;
        toto.c = 8;
        toto.d = 567890;
        toto.l = 'K';
        m_com.sendEvent("TOTO", &toto, sizeof(POPI));
    }


public:
    void onReceiveEventKoala(void *data, unsigned int size) {
        int *newData = (int *)data;

        qDebug() << "receive KOALA event :";
        qDebug() << *newData;
    }

    void onReceiveEventPopole(void *data, unsigned int size) {
        static int u = 0;
        qDebug() << size;
        if (u % 2 == 0) {
            qDebug() << "receive POPOLE event 4";
            int *intLol = (int *)data;
            qDebug() << *intLol;
        } else {
            qDebug() << "receive POPOLE event 1";
            char *intLol = (char *)data;
            qDebug() << *intLol;
        }
        ++u;
    }

private:
    ClientCommunication &m_com;
};

#endif // TESTCONNECTION_H
