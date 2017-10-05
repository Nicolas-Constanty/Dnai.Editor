#include "focusmanager.h"

FocusManager::FocusManager()
{

}

FocusManager::~FocusManager() {}


void FocusManager::registerItem(QQuickItem *item)
{
    if (!m_items.contains(item))
        m_items.append(item);
}

void FocusManager::deleteItem(QQuickItem *item)
{
    if (m_items.contains(item))
        m_items.removeOne(item);
}

QList<QQuickItem *> FocusManager::findFocused(const QPointF &point)
{
    QList<QQuickItem *> items;
    for (auto i = 0; i < m_items.size(); ++i) {
        auto item = m_items.at(i);
        if (item->contains(point - item->position()))
            items.append(item);
    }
    return items;
}

FocusManagerIo::FocusManagerIo()
{

}

FocusManagerIo::~FocusManagerIo() {}


QList<QQuickItem *> FocusManagerIo::findFocused(const QPointF &point)
{
    QList<QQuickItem *> items;
    for (auto i = 0; i < m_items.size(); ++i) {
	    auto item = m_items.at(i);
        if (item->contains(point -item->parentItem()->parentItem()->parentItem()->parentItem()->position() -item->parentItem()->parentItem()->parentItem()->position() -item->parentItem()->parentItem()->position() -item->parentItem()->position() - item->position()))
            items.append(item);
    }
    return items;
}
