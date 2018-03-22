#ifndef DNAI_MODELS_TREEITEM_H
#define DNAI_MODELS_TREEITEM_H

#include <QList>
#include <QVariant>
#include <QVector>
#include "entity.h"

namespace dnai
{
	namespace models
	{
		template<class T>
		class TreeItem
		{
		public:
			explicit TreeItem(T *parent = 0);
			~TreeItem();

			T *child(int number);
			int childCount() const;
			bool insertChild(int position, T *);
			void appendChild(T *);
			T *parent();
			bool removeChildren(int position, int count);
			int childNumber() const;
			QList<T*> &children() const;

		private:
			QList<T*> m_childItems;
			T *m_parentItem;
		};

		template <class T>
		TreeItem<T>::TreeItem(T* parent) : m_parentItem(parent)
		{
		}

		template <class T>
		TreeItem<T>::~TreeItem()
		{
		}

		template <class T>
		T* TreeItem<T>::child(int number)
		{
			return m_childItems.at(number);
		}

		template <class T>
		int TreeItem<T>::childCount() const
		{
			return m_childItems.count();
		}

		template <class T>
		bool TreeItem<T>::insertChild(int position, T *e)
		{
			if (position < 0 || position > m_childItems.count())
				return false;
			m_childItems.insert(position, e);
		}

		template <class T>
		void TreeItem<T>::appendChild(T* e)
		{
			m_childItems.append(e);
		}

		template <class T>
		T* TreeItem<T>::parent()
		{
			return m_parentItem;
		}

		template <class T>
		bool TreeItem<T>::removeChildren(int position, int count)
		{
			if (position < 0 || position > m_childItems.count())
				return false;
			auto max = position + count;
			if (max > m_childItems.count())
				max = m_childItems.count();
			for (auto i = position; i < max; i++)
				delete m_childItems.takeAt(i);
			return true;
		}

		template <class T>
		int TreeItem<T>::childNumber() const
		{
			return m_childItems.count();
		}

		template <class T>
		QList<T*> &TreeItem<T>::children() const
		{
			return m_childItems;
		}
	}
}

#endif // DNAI_MODELS_TREEITEM_H
