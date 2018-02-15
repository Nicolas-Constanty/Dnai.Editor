#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include "dnai/project.h"


namespace dnai {
namespace models {
class TreeItem;

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    enum Roles {
        NameRole = Qt::UserRole + 1,
        ItemRole
    };
    explicit TreeModel(QObject *parent = nullptr) : QAbstractItemModel(parent) {}
    TreeModel(const Project *project, QObject *parent = 0);
    ~TreeModel();

    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    dnai::models::Common *matchModel(dnai::models::Common *c);
    QModelIndexList match(const QModelIndex &start, int role, const QVariant &value, int hits, Qt::MatchFlags flags) const override;

private:
    void setupModelData(const Project *project, TreeItem *parent);
    void setupContextModel(models::Context *context, TreeItem *parent, int currentIdx);
    void setupClassModel(models::Class *cl, TreeItem *parent, int currentIdx);
    void setupFunctionModel(models::Function *func, TreeItem *parent, int currentIdx);

    TreeItem *rootItem;
    Common *matchModelRecur(TreeItem *ti, Common *c);
    QHash<int, QByteArray> roleNames() const;
};
}
}

Q_DECLARE_METATYPE(dnai::models::TreeModel *)

#endif // TREEMODEL_H
