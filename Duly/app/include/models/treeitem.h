#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QVariant>
#include <QModelIndex>
#include "imodel.h"

namespace duly_gui {
namespace models {
class TreeItem
{
public:
    explicit TreeItem(const QList<QVariant> &data, TreeItem *parentItem = 0);
    ~TreeItem();

    void appendChild(TreeItem *child);

    TreeItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    TreeItem *parentItem();
    const QModelIndex &idxmodel() const { return m_idx; }
    void setIdx(const QModelIndex &ref);
    IModel *model() const { return m_model; }
    void setModel(IModel *);

private:
    QList<TreeItem*> m_childItems;
    QList<QVariant> m_itemData;
    TreeItem *m_parentItem;
    QModelIndex m_idx;
    IModel *m_model;
};
}
}
#endif // TREEITEM_H
