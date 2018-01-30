#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QVariant>
#include <QModelIndex>
#include "common.h"

namespace duly_gui {
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
    duly_gui::models::Common *model() const { return m_model; }
    void setModel(duly_gui::models::Common *);

private:
    QList<TreeItem*> m_childItems;
    QList<QVariant> m_itemData;
    TreeItem *m_parentItem;
    QModelIndex m_idx;
    duly_gui::models::Common *m_model;
};
}
}
#endif // TREEITEM_H
