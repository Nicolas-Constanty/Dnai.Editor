#ifndef OBSERVABLELIST_H
#define OBSERVABLELIST_H

#include <QObject>
#include <list>
#include <memory>

class BaseObservable : public QObject
{
    Q_OBJECT
public:
    explicit BaseObservable(QObject *parent = nullptr) : QObject(parent) {}
    enum NotificationType {
        AddItem,
        RemoveItem,
        ClearList
    };

signals:
    void listChanged(NotificationType t);
};

template<class T>
class ObservableList : public BaseObservable
{

public:
    explicit ObservableList(QObject *parent = nullptr) : BaseObservable(parent) {}

    bool Empty() const { return m_list.empty(); }

    const std::list<T> &rawList() const {return m_list;}

    void Add(const T &ref)
    {
        m_item = ref;
        m_list.push_back(ref);
        emit listChanged(NotificationType::AddItem);
    }

    void Remove(const T &ref)
    {
        m_item = ref;
        m_list.remove(ref);
        emit listChanged(NotificationType::RemoveItem);
    }
    void Clear()
    {
        m_list.clear();
        emit listChanged(NotificationType::ClearList);
    }

private:
    std::list<T> m_list;
    T m_item;
};


#endif // OBSERVABLELIST_H
