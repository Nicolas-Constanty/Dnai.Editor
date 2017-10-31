#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <vector>
#include <map>
#include <QString>
#include <list>
#include <exception>

class DulyCommunicationServer;

class EventManager
{
public:
    class Event {
    public:
        Event(unsigned int size,
              QString const &name);
        Event(Event const &);
        Event &operator=(Event const &);

        void compute(void *data, unsigned int size);
        void operator<<(DulyCommunicationServer *);
        void operator>>(DulyCommunicationServer *);

        unsigned int getSize() const;

    private:
        unsigned int m_size;
        QString m_name;
        std::list<DulyCommunicationServer *> m_clients;
    };

    friend class Event;

private:
    EventManager();

public:
    static EventManager &shared();

public:
    int addClientToEvent(QString const &eventName,
                          unsigned int size,
                          DulyCommunicationServer *);

    Event &getFrom(int id) throw(std::runtime_error);
    Event &getFrom(QString const &name) throw(std::runtime_error);
    void removeClient(DulyCommunicationServer *);


private:
    std::vector<Event> m_events;
    std::map<size_t, Event> m_indexTab;
};

#endif // EVENTMANAGER_H
