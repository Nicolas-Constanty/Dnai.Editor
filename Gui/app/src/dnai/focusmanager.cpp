#include "dnai/focusmanager.h"
#include "dnai/views/genericnode.h"

namespace dnai
{
	FocusManager::FocusManager()
    {}

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

            if (item->contains(point
                - item->position()))
            {
                items.append(item);
            }
        }
        return items;
	}

	QList<QQuickItem*> &FocusManager::getList()
	{
		return m_items;
	}

	FocusManagerIo::FocusManagerIo()
	{}

	FocusManagerIo::~FocusManagerIo() {}


	QList<QQuickItem *> FocusManagerIo::findFocused(const QPointF &point)
	{
		QList<QQuickItem *> items;
        for (auto i = 0; i < m_items.size(); ++i) {
			auto item = m_items.at(i);
            item->setProperty("isHover", false);
//            qDebug() << "Pos 1" << item->contains(point);
//            qDebug() << "Pos 2" <<  item->contains(point - item->position());
//            qDebug() << "Pos 3" <<  item->contains(point - item->position() - item->parentItem()->position());
//            qDebug() << "Pos 4" <<  item->contains(point - item->position() - item->parentItem()->position() - item->parentItem()->parentItem()->position());
//            qDebug() << "Pos 5" <<  item->contains(point - item->position() - item->parentItem()->position() - item->parentItem()->parentItem()->position() - item->parentItem()->parentItem()->parentItem()->position());
//            qDebug() << "Pos 6" <<  item->contains(point - item->position() - item->parentItem()->position() - item->parentItem()->parentItem()->position() - item->parentItem()->parentItem()->parentItem()->position() - item->parentItem()->parentItem()->parentItem()->parentItem()->position());
			auto p = item;
			auto np = point;
			while (dynamic_cast<views::GenericNode *>(p) == nullptr)
			{
				np -= p->position();
				p = p->parentItem();
			}
            if (item->contains(np))
				items.append(item);
        }
		return items;
	}

}
