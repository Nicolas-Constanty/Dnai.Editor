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

public slots:
    void update() {
        int a = 1234;
        m_com.sendEvent("YOLO", &a, 4);
    }

public:
    void onReceiveEventKoala(void *data, unsigned int size) {
        int *newData = (int *)data;

        qDebug() << "receive KOALA event :";
        qDebug() << *newData;
    }

private:
    ClientCommunication &m_com;
};

#endif // TESTCONNECTION_H
