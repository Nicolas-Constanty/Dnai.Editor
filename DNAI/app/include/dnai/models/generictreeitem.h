#ifndef DNAI_MODELS_GENERICTREEITEM_H
#define DNAI_MODELS_GENERICTREEITEM_H

#include <QModelIndex>

namespace dnai
{
	namespace models
	{
		class GenericTreeItem : public QObject
		{
			Q_OBJECT
		public:
			explicit GenericTreeItem(QObject *parent = nullptr) : QObject(parent), m_parentItem(nullptr)
			{
			}

			explicit GenericTreeItem(const QList<QVariant> &data, GenericTreeItem *parentItem = nullptr) : QObject(nullptr),
			                                                                                               m_parentItem(parentItem)
			{
                m_itemData = data;
			}

            virtual ~GenericTreeItem() = default;
			void appendChild(GenericTreeItem *child) { m_childItems.append(child); }
			GenericTreeItem *child(int row) const { return m_childItems.at(row); }
			const QList<GenericTreeItem *> &children() const { return m_childItems; }

			int childCount() const { return m_childItems.count(); }
			int columnCount() const { return m_itemData.count(); }

			QVariant data(int column) const { return m_itemData.at(column); }
			int row() const
			{
//				if (m_parentItem)
//                                    return m_parentItem->m_childItems.indexOf(static_cast<T *const&>(this));
				return 0;
			}
			GenericTreeItem *parentItem() const { return m_parentItem; }
			const QModelIndex &idxmodel() const { return m_idx; }
			void setIdx(const QModelIndex &ref)
			{
				if (ref == m_idx)
					return;
				m_idx = ref;
			}

		private:
			QList<GenericTreeItem*> m_childItems;
			QList<QVariant> m_itemData;
			GenericTreeItem *m_parentItem;
			QModelIndex m_idx;

		};
	}
}

#endif //DNAI_MODELS_GENERICTREEITEM_H
