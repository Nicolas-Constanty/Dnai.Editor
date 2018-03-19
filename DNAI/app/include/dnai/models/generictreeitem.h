#ifndef DNAI_MODELS_GENERICTREEITEM_H
#define DNAI_MODELS_GENERICTREEITEM_H

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

            virtual ~GenericTreeItem() = default;
            void appendChild(T *child) {
                m_childItems.append(child);
            }
            T *child(int row) const { return m_childItems.at(row); }
            const QList<T *> &children() const { return m_childItems; }

            int childCount() const { return m_childItems.count(); }
            virtual int columnCount() const = 0;
            int row() const
            {
                if (m_parentItem)
                    m_parentItem->m_childItems.indexOf(const_cast<T*>(dynamic_cast<const T *>(this)));
                return 0;
            }
            T *parentItem() const { return m_parentItem; }
            const QModelIndex &idxmodel() const { return m_idx; }
            void setIdx(const QModelIndex &ref)
            {
                if (ref == m_idx)
                    return;
                m_idx = ref;
            }

        private:
            QList<T*> m_childItems;
            T *m_parentItem;
            QModelIndex m_idx;

        };
    }
}

#endif //DNAI_MODELS_GENERICTREEITEM_H
