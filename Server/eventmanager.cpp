#include <QDebug>
#include <dulycommunicationserver.h>
#include "eventmanager.h"

EventManager::EventManager()
{

}

EventManager &EventManager::shared() {
    static EventManager eventManager;

    return (eventManager);
}

int EventManager::addClientToEvent(QString const &eventName,
                                    unsigned int size,
                                    DulyCommunicationServer *communication) {
    static std::hash<std::string> h1;

    size_t str_hash = h1(eventName.toStdString());
    std::map<size_t, Event>::iterator it = m_indexTab.find(str_hash);

    if (it != m_indexTab.end()) {
        it->second << communication;
        return (1);
    } else {
        Event event(size, eventName);
        event << communication;
        m_indexTab.emplace(str_hash, event);
        return (0);
    }

    return (-1);


/*    std::map<QString, int>::const_iterator it = m_indexTab.find(eventName);
    int idx = 0;

    if (it == m_indexTab.end()) {
        unsigned int eventsSize = m_events.size();
        qDebug() << eventsSize;
        idx = eventsSize;
        m_indexTab[eventName] = eventsSize;

        Event event(size, eventName);
        event << communication;
        m_events.push_back(event);
        qDebug() << "added from new event" << communication;
    } else {
        m_events[it->second] << communication;
        idx = it->second;
        qDebug() << "added " << communication;
    }
    return (idx);*/
}

EventManager::Event &EventManager::getFrom(int id) throw(std::runtime_error) {
    if ((int)m_events.size() < id) {
        throw std::runtime_error("wrong id");
    }

    return (m_events[id]);
}

EventManager::Event &EventManager::getFrom(QString const &name) throw(std::runtime_error) {
    static std::hash<std::string> h1;

    size_t str_hash = h1(name.toStdString());

    std::map<size_t, Event>::iterator it = m_indexTab.find(str_hash);
    if (it == m_indexTab.end()) {
        throw std::runtime_error("BAD NAME " + name.toStdString());
    }

    return (it->second);
}

void EventManager::removeClient(DulyCommunicationServer *client) {
    std::map<size_t, Event>::iterator it = m_indexTab.begin();

    while (it != m_indexTab.end()) {
        it->second >> client;
        ++it;
    }
}

EventManager::Event::Event(unsigned int size,
                           QString const &name) :
    m_size(size), m_name(name), m_clients() {

}

EventManager::Event::Event(Event const &other) {
    *this = other;
}

EventManager::Event &EventManager::Event::operator=(Event const &other) {
    this->m_clients = other.m_clients;
    this->m_size = other.m_size;
    this->m_name = other.m_name;
    return (*this);
}

unsigned int EventManager::Event::getSize() const {
    return (this->m_size);
}

void EventManager::Event::compute(void *data, unsigned int size) {
    for (DulyCommunicationServer *com : m_clients) {
        com->send(data, size);
    }
}

void EventManager::Event::operator<<(DulyCommunicationServer *com) {
    m_clients.push_back(com);
}

void EventManager::Event::operator>>(DulyCommunicationServer *com) {
    m_clients.remove(com);
}
