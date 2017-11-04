#include "focusmanager.h"
#include "views/scalableitem.h"

namespace duly_gui
{
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
            const auto item = static_cast<views::ScalableItem *>(m_items.at(i));
            auto p = item->mapToItem(item, point);
            qDebug() << p;
            if (item->contains(p))
				items.append(item);
		}
		return items;
	}

	QList<QQuickItem*> &FocusManager::getList()
	{
		return m_items;
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
            const auto si = dynamic_cast<views::ScalableItem *>(item->parentItem()->parentItem()->parentItem()->parentItem()->parentItem());
            if (item->contains(point / si->scaleFactor()
                - item->parentItem()->parentItem()->parentItem()->parentItem()->position() / si->scaleFactor()
                - item->parentItem()->parentItem()->parentItem()->position() / si->scaleFactor()
                - item->parentItem()->parentItem()->position() / si->scaleFactor()
                - item->parentItem()->position() / si->scaleFactor()
                - item->position() / si->scaleFactor()))
				items.append(item);
		}
		return items;
	}

}
