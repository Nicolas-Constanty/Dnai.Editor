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
            explicit GenericTreeItem(GenericTreeItem *parent = nullptr) : QObject(nullptr), m_parentItem(parent)
            {
            }

            virtual ~GenericTreeItem() = default;
            void appendChild(GenericTreeItem *child) {
                m_childItems.append(child);
            }
            GenericTreeItem *child(int row) const { return m_childItems.at(row); }
            const QList<GenericTreeItem *> &children() const { return m_childItems; }

            int childCount() const { return m_childItems.count(); }
            virtual int columnCount() const = 0;
            int row() const
            {
                if (m_parentItem)
                    m_parentItem->m_childItems.indexOf(const_cast<GenericTreeItem*>(this));
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
            GenericTreeItem *m_parentItem;
            QModelIndex m_idx;

        };
    }
}

#endif //DNAI_MODELS_GENERICTREEITEM_H
