#ifndef DNAI_MODELS_GENERICTREEITEM_H
#define DNAI_MODELS_GENERICTREEITEM_H

#include <exception>

#include <QDebug>
#include <QModelIndex>

namespace dnai
{
    namespace models
    {
		template<class T>
        class GenericTreeItem : public QObject
        {
        public:
            explicit GenericTreeItem(T *parent = nullptr) : QObject(nullptr), m_parentItem(parent)
            {
            }

            virtual ~GenericTreeItem()
            {
            }
            virtual void appendChild(T *child) {
                child->m_parentItem = dynamic_cast<T *>(this);

                if (child->m_parentItem == nullptr)
                {
                    qWarning() << "!!!!!! Your are trying to append a child with incompatible type in GenericTreeItem !!!!!!";
                    throw std::runtime_error("Your are trying to append a child with incompatible type in GenericTreeItem");
                }

                m_childItems.append(child);
            }
            T *child(int row) const { return m_childItems.at(row); }
            const QList<T *> &childrenItem() const { return m_childItems; }

            int childCount() const { return m_childItems.count(); }
            virtual int columnCount() const = 0;
            virtual int row() const
            {
                if (m_parentItem)
                    return m_parentItem->m_childItems.indexOf(const_cast<T*>(dynamic_cast<const T *>(this)));
                return 0;
            }
            T *parentItem() const { return m_parentItem; }
            QModelIndex idxmodel() const { return m_idx; }
            void setIdx(const QModelIndex &ref)
            {
                if (ref == m_idx)
                    return;
                m_idx = ref;
            }
			void removeOne(T *e)
            {
				if (m_childItems.contains(e))
					m_childItems.removeOne(e);
            }

            void deleteChildren()
            {
                while (!m_childItems.isEmpty())
                    delete m_childItems.takeFirst();
            }

            void removeChildren()
            {
                while (!m_childItems.isEmpty())
                {
                    m_childItems.takeFirst()->m_parentItem = nullptr;
                }
            }

        private:
            QList<T*> m_childItems;
            T *m_parentItem;
            QModelIndex m_idx;

        };
    }
}

#endif //DNAI_MODELS_GENERICTREEITEM_H
