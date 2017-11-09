#include <QCoreApplication>
#include <QHostAddress>
#include "dulycommunicationserver.h"
#include "authentificationpackage.h"
#include "eventsendpackage.h"
#include "eventregisterpackage.h"
#include "clientcommunication.h"
#include <functional>
#include <QObject>
#include "testclass.h"

//ClientCommunication *com;//(QHostAddress::LocalHost, 7777, "YOLO");


typedef struct {
    int i;
    char b;
    float u;
} DataToto;
/*
class tutu : public QObject {
   Q_OBJECT

public:
    tutu(ClientCommunication &com)
        : QObject(),
        com(com)
    {

    }

//public slots:
    void call() {
        qDebug() << "TIMER CALL";
        char c = 'C';
        com.sendEvent("TOTO", &c, sizeof(c));
    }

public:
    void toto(void *koala, unsigned int size) {
        char *data = (char *)koala;
        qDebug() << size;
        qDebug() << *data;
        qDebug() << "YOLOLOLO";
        qDebug() << QThread::currentThread();
    }

private:
    ClientCommunication &com;
};*/

#include <QTimer>
/*int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qRegisterMetaType<size_t>();

    qDebug() << "main:" << QThread::currentThread();

    ClientCommunication com(QHostAddress::LocalHost, 7777, "YOLO");
    com.start();

    tutu lol(com);
//    char c = 'C';

    std::function<void (void *, unsigned int)> functionLol = std::bind(&tutu::toto, &lol, std::placeholders::_1, std::placeholders::_2);
    com.registerEvent("TOTO", 1, functionLol);
    std::function<void (void *, unsigned int)> functionLol2 = std::bind(&tutu::tata, &lol, std::placeholders::_1, std::placeholders::_2);
    com.registerEvent("TATA", 10000, functionLol2);

  //  std::function<void (void *, unsigned int)> functionLol3 = std::bind(&tutu::koalaptr, &lol, std::placeholders::_1, std::placeholders::_2);
  //  com.registerEvent("KOALA", sizeof(tutu::KOALALOL), functionLol3);

    //lol.callTata();
    //lol.callKoala();

   // lol.callToto();
    //lol.callTata();
    //lol.callTata();
    //lol.callTata();

   // QTimer *timer = new QTimer();
   // QObject::connect(timer, SIGNAL(timeout()), &lol, SLOT(callTata()));
   // timer->start(2000);

//    QTimer::singleShot(1000, &lol, SLOT(callToto()));
//    QTimer::singleShot(5000, &lol, SLOT(callTata()));

    return a.exec();
}
*/
