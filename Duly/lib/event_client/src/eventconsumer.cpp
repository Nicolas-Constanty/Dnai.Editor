#include <QDebug>
#include <functional>
#include "clientmanager.h"
#include "include/eventconsumer.h"

EventConsumer::EventConsumer(QObject *parent)
    : QObject(parent),
      m_clientName(),
      m_eventName(),
      m_description(),
      m_com(NULL)
{
}

QString const &EventConsumer::clientName() const {
    return (m_clientName);
}

QString const &EventConsumer::eventName() const {
    return (m_eventName);
}

QString const &EventConsumer::description() const {
    return (m_description);
}

void EventConsumer::checkInit() {
    if (!m_clientName.isEmpty()
        && !m_eventName.isEmpty()
        && !m_description.isEmpty()) {
        onPropertiesInit();
    }
}

void EventConsumer::receiveData(void *data, unsigned int size) {
    //CHANGER LA DATA EN FONCTION DE LA DESCRIPTION
    // CALL DU SIGNAL

    //int *newData = (int *)data;
    (void)(size);
    QVariantList listVar;

    QList<DescriptionParser::TypeParser> const &list = m_parser.getList();
    unsigned int sizeInc = 0;
    foreach (DescriptionParser::TypeParser const &info, list) {
        QVariant var;
        char *str = (char *)malloc(info.size + 1);
        memcpy(str, (char *)data + sizeInc, info.size);

        switch (info.firstLetter) {
        case 'C':
        {
            str[info.size] = '\0';
            var = QVariant(QString(str));
            break;
        }
        case 'L':
        {
            int *dataInt = (int *)str;
            var = QVariant(*dataInt);
            break;
        }
        case 'D':
        {
            double *dataDouble = (double *)str;
            var = QVariant(*dataDouble);
            break;
        }
        case 'F':
        {
            float *dataFloat = (float *)str;
            var = QVariant(*dataFloat);
            break;
        }
        case 'S':
        {
            short *dataShort = (short *)str;
            var = QVariant(*dataShort);
            break;
        }
        default:
        {
            break;
        }
        }

        listVar << var;
        free(str);
        sizeInc += info.size;
    }


    emit receiveEvent(listVar);
}

void EventConsumer::onPropertiesInit() {
    m_com = ClientManager::shared().getFrom(m_clientName);
    if (m_com == NULL) {
        qDebug() << "[WARNING] no client found for " << m_clientName;
    } else {
        m_parser.parse(m_description);
        QList<DescriptionParser::TypeParser> const &list = m_parser.getList();
        unsigned int size = 0;
        foreach (DescriptionParser::TypeParser const &info, list) {
            size += info.size;
        }
        m_com->registerEvent(m_eventName, size, std::bind(&EventConsumer::receiveData, this, std::placeholders::_1, std::placeholders::_2));
    }
}

void EventConsumer::setClientName(QString const &clientName) {
    m_clientName = clientName;
    checkInit();
    emit clientNameChanged();
}

void EventConsumer::setEventName(QString const &eventName) {
    m_eventName = eventName;
    checkInit();
    emit eventNameChanged();
}

void EventConsumer::setDescription(QString const &description) {
    m_description = description;
    checkInit();
    emit descriptionChanged();
}
