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

class Q_DECL_EXPORT ClientCommunication : public QThread
{

    Q_OBJECT

public:
    ClientCommunication(QHostAddress addr, quint16 port, QString name);

protected:
    void run();

signals:
    void runStarted();

private slots:
    void onRunStarted();
    void onReceiveSendEventSignal(QByteArray *);

public:
    void registerEvent(QString const &eventName,
                       unsigned int size,
                       std::function<void (void *, unsigned int)> func);
    void sendEvent(QString const &name, void *data, unsigned int size);

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
