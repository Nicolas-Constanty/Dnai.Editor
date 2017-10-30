#ifndef CLIENTCOMMUNICATION_H
#define CLIENTCOMMUNICATION_H

#include <QObject>
#include <QThread>
#include <QHostAddress>
#include <QList>
#include "dulycommunicationserver.h"
#include "eventregisterpackage.h"
#include "eventsendpackage.h"
#include <QSemaphore>

class ClientCommunication : public QThread
{

    Q_OBJECT
//    typedef void (*calledObjFunction)(void *, unsigned int);

public:
    ClientCommunication(QHostAddress addr, quint16 port, QString name);

//signals:
  //  void receiveEvent(void *, unsigned int);

protected:
    void run();

signals:
    void runStarted();
  //  void sendEvent(const QString &name, void *data, unsigned int size);

public slots:
    void onRunStarted();
    void onReceiveSendEventSignal(QByteArray *);
   // void onReveiveNewEventName(QString name, unsigned int);

public:
    void registerEvent(QString const &eventName,
                       unsigned int size,
                       std::function<void (void *, unsigned int)> func) {

        static std::hash<std::string> h1;

        size_t str_hash = h1(eventName.toStdString());
//        std::map<size_t, Event>::iterator it = m_indexTab.find(str_hash);

        if (!m_com)
            m_sem.acquire();


        m_eventsRegister.emplace(str_hash, EventCallBack(eventName, func));

//        m_eventsUnk.push_back(EventCallBack(eventName, func));
//        m_func = func;

        SendEventRegisterPackage eventRegister2;
        createEventRegisterPackage(eventRegister2, eventName, size, true);
        m_com->send(&eventRegister2, sizeof(eventRegister2));
    }

  /*  int getIdFromName(QString const &name) {
        int i = 0;
        while (i < m_events.size()) {
            if (name == m_events[i].name) {
                return (i);
            }
            ++i;
        }
        return (-1);
    }*/

public slots:
    void sendEvent(QString const &name, void *data, unsigned int size) {
        //char u = 'C';

        SendEventSendFromClientPackage *eventSendPackage = createEventSendFromClientPackage(name, data, size);

        emit m_com->sendDataAllocated(eventSendPackage, sizeof(SendEventSendFromClientPackage) + size);

      //  int id = getIdFromName(name);// name;
      /*  if (id == -1) {
            qDebug() << "there is no " + name;
            return ;
        }
        qDebug() << "id : " << id << " from name: " << name;

        SendEventSendPackage *eventSendPackage = createEventSendPackage(id, data, size);

        qDebug() << eventSendPackage->header.packageSize;

        emit m_com->sendData(eventSendPackage, sizeof(SendEventSendPackage) + size);
    */

    }

private:
    typedef struct s_eventCallBack {
    public:
        QString name;
        std::function<void (void *, unsigned int)> func;
        s_eventCallBack(QString const &name, std::function<void (void *, unsigned int)> func) {
            this->name = name;
            this->func = func;
        }
         s_eventCallBack( s_eventCallBack const &other) {
           *this = other;
        }

         s_eventCallBack &operator=( s_eventCallBack const &other) {
            name = other.name;
            func = other.func;
            return (*this);
        }

    } EventCallBack;

private:
    DulyCommunicationServer *m_com;
    QHostAddress m_addr;
    quint16 m_port;
    QString m_name;
    std::function<void (void *, unsigned int)> m_func;
    QSemaphore m_sem;
    std::vector<EventCallBack>    m_events;
    QList<EventCallBack> m_eventsUnk;

    std::map<size_t, EventCallBack> m_eventsRegister;

};

#endif // CLIENTCOMMUNICATION_H
