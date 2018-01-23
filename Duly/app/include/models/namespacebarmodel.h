#ifndef NAMESPACEBARMODEL_H
#define NAMESPACEBARMODEL_H
#include "namespacebaritem.h"
#include <QAbstractListModel>

namespace duly_gui {
namespace models {
class NameSpaceBarModel : public QAbstractListModel
{
    Q_OBJECT
public:
    NameSpaceBarModel(QObject *parent = 0) : QAbstractListModel(parent) {}
    explicit NameSpaceBarModel(QList<NameSpaceBarItem *> list, QObject *parent = 0);
    // QAbstractItemModel interface
public:
//    QModelIndex index(int row, int column, const QModelIndex &parent) const;
//    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
//    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
//    bool setData(const QModelIndex &index, const QVariant &value, int role);

private:
    QList<QVariant> m_list;
};
}
}


#endif // NAMESPACEBARMODEL_H
