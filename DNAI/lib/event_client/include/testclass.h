#ifndef TESTCLASS_H
#define TESTCLASS_H

#include <QObject>
#include "clientcommunication.h"
#include <QThread>

class tutu : public QObject {
   Q_OBJECT

public:
    tutu(ClientCommunication &com)
        : QObject(),
        com(com)
    {

    }

    typedef struct koala {
        int a;
        char x;
        float u;
    } KOALALOL;

public slots:
    void callToto() {
        char c = 'Y';
        com.sendEvent("TOTO", &c, sizeof(c));
    }
    void callTata() {
        char c[10000];// = (char *)malloc(10000);
        memset(c, 0, 10000);
        com.sendEvent("TATA", c, 10000);
    }
    void callKoala() {
        KOALALOL c = {12, 'L', 9.43};
        com.sendEvent("KOALA", &c, sizeof(c));
    }


public:
    void toto(void *koala, unsigned int size) {
        char *data = (char *)koala;
        qDebug() << size;
        qDebug() << (*data);
        qDebug() << "TOTO";
        qDebug() << QThread::currentThread();
    }

    void tata(void *koala, unsigned int size) {
        //int *data = (int *)koala;
        qDebug() << "SIZE: "  << size;
        //qDebug() << (*data);
        qDebug() << "TATA";
        qDebug() << QThread::currentThread();
    }

    void koalaptr(void *koala, unsigned int size) {
        KOALALOL *data = (KOALALOL *)koala;
        qDebug() << "SIZE: "  << size;
        qDebug() << data->a;
        qDebug() << data->x;
        qDebug() << data->u;
        qDebug() << "KOALA";
        qDebug() << QThread::currentThread();
    }

private:
    ClientCommunication &com;
};

#endif // TESTCLASS_H
