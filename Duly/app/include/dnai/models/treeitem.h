#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QVariant>
#include <QModelIndex>
#include "common.h"

namespace dnai {
namespace models {
class TreeItem : public QObject
{
    Q_OBJECT
public:
    TreeItem(QObject *parent = nullptr) : QObject(parent) {}
    explicit TreeItem(const QList<QVariant> &data, TreeItem *parentItem = 0);
    ~TreeItem();

    void appendChild(TreeItem *child);

    TreeItem *child(int row);
    const QList<TreeItem*> &children() const { return m_childItems; }
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    TreeItem *parentItem();
    const QModelIndex &idxmodel() const { return m_idx; }
    void setIdx(const QModelIndex &ref);
    dnai::models::Common *model() const { return m_model; }
    void setModel(dnai::models::Common *);

private:
    QList<TreeItem*> m_childItems;
    QList<QVariant> m_itemData;
    TreeItem *m_parentItem;
    QModelIndex m_idx;
    dnai::models::Common *m_model;
};
}
}
#endif // TREEITEM_H
