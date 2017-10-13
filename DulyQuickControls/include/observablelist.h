#ifndef OBSERVABLELIST_H
#define OBSERVABLELIST_H

#include <QObject>
#include <list>
#include <memory>

namespace duly_gui
{
	class BaseObservable : public QObject
	{
		Q_OBJECT
	public:
		explicit BaseObservable(QObject *parent = nullptr) : QObject(parent) {}
		/**
		* \brief Notification Type Enum
		*/
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

		/**
		* \brief is list is empty?
		* \return bool
		*/
		bool empty() const { return m_list.empty(); }

		/**
		* \brief return the std list
		* \return std::list<T> &
		*/
		const std::list<T> &rawList() const { return m_list; }

		/**
		* \brief add an item
		* \param ref
		*/
		void add(const T &ref)
		{
			m_item = ref;
			m_list.push_back(ref);
			emit listChanged(NotificationType::AddItem);
		}

		/**
		* \brief remove an item
		* \param ref
		*/
		void remove(const T &ref)
		{
			m_item = ref;
			m_list.remove(ref);
			emit listChanged(NotificationType::RemoveItem);
		}

		/**
		* \brief remove all item
		*/
		void clear()
		{
			m_list.clear();
			emit listChanged(NotificationType::ClearList);
		}

	private:
		std::list<T> m_list;
		T m_item;
	};

}

#endif // OBSERVABLELIST_H
