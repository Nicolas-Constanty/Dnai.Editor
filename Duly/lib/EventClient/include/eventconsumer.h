#ifndef EVENTCONSUMER_H
#define EVENTCONSUMER_H

#include <QObject>
#include <QString>
#include <QVariantList>
#include "clientcommunication.h"
#include "descriptionparser.h"

class Q_DECL_EXPORT EventConsumer : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString clientName READ clientName WRITE setClientName NOTIFY clientNameChanged)
    Q_PROPERTY(QString eventName READ eventName WRITE setEventName NOTIFY eventNameChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)

public:
    EventConsumer(QObject *parent = 0);

private:
    void checkInit();
    void onPropertiesInit();
    void receiveData(void *data, unsigned int size);

public:
    QString const &clientName() const;
    QString const &eventName() const;
    QString const &description() const;

public:
    void setClientName(QString const &);
    void setEventName(QString const &);
    void setDescription(QString const &);

signals:
    void receiveEvent(QVariantList data);
    void clientNameChanged();
    void eventNameChanged();
    void descriptionChanged();

private:
    QString m_clientName;
    QString m_eventName;
    QString m_description;
    ClientCommunication *m_com;
    DescriptionParser m_parser;
};

#endif // EVENTCONSUMER_H
