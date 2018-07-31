#ifndef FOCUSMANAGER_H
#define FOCUSMANAGER_H

#include <QtQuick/QQuickItem>

namespace dnai
{
	class FocusManager
	{
	public:
		FocusManager();
		virtual ~FocusManager();
		/**
		* \brief Register a QQuickItem
		* \param item
		*/
		void registerItem(QQuickItem *item);

		/**
		* \brief Delete a register QQuickItem
		* \param item
		*/
		void deleteItem(QQuickItem *item);

		/**
		* \brief Return a list of focused elements by the mouse
		* \param point
		* \return
		*/
		virtual QList<QQuickItem *> findFocused(const QPointF &point);

		/**
		* \brief Return the list
		* \return QList<QQuickItem *> &
		*/
		QList<QQuickItem *> &getList();

	protected:
		QList<QQuickItem *> m_items;
	};

	class FocusManagerIo : public FocusManager
	{
	public:
		FocusManagerIo();
		~FocusManagerIo();

		/**
		* \brief Return a list of focused elements by the mouse
		* \param point
		* \return
		*/
		virtual QList<QQuickItem *> findFocused(const QPointF &point) override;
	};
}

#endif // FOCUSMANAGER_H
