#include "models/treeitem.h"
#include "models/treemodel.h"

#include <QStringList>
#include <QDebug>

namespace duly_gui {
namespace models {
TreeModel::TreeModel(const Project *project, QObject *parent)
    : QAbstractItemModel(parent)
{
    QList<QVariant> rootData;
    rootData << "Name";
    rootItem = new TreeItem(rootData);
    setupModelData(project, rootItem);
}

TreeModel::~TreeModel()
{
    delete rootItem;
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    return item->data(index.column());
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return QAbstractItemModel::flags(index);
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent)
            const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parentItem();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

void TreeModel::setupContextModel(const models::Context *context, TreeItem *parent)
{
    QList<QVariant> columnData;
    columnData.append(QVariant(context->name()));

    auto temp = new TreeItem(columnData, parent);
    parent->appendChild(temp);

    const auto contexts = context->contexts();
    for (auto i = 0; i < contexts.size(); i++)
        setupContextModel(contexts[i], temp);

    const auto classes = context->classes();
    qDebug() << classes.size();
    for (auto i = 0; i < classes.size(); i++)
        setupClassModel(classes[i], temp);

    const auto functions = context->functions();
    for (auto i = 0; i < functions.size(); i++)
        setupFunctionModel(functions[i], temp);
}

void TreeModel::setupClassModel(const models::Class *cl, TreeItem *parent)
{
    QList<QVariant> columnData;
    columnData.append(QVariant(cl->name()));

    auto temp = new TreeItem(columnData, parent);
    parent->appendChild(temp);

    const auto classes = cl->classes();
    for (auto i = 0; i < classes.size(); i++)
        setupClassModel(classes[i], temp);

    const auto functions = cl->functions();
    for (auto i = 0; i < functions.size(); i++)
        setupFunctionModel(functions[i], temp);
}

void TreeModel::setupFunctionModel(const models::Function *func, TreeItem *parent)
{
    QList<QVariant> columnData;
    columnData.append(func->name());

    TreeItem *temp = new TreeItem(columnData, parent);
    parent->appendChild(temp);
}

void TreeModel::setupModelData(const Project *project, TreeItem *parent)
{
    setupContextModel(project->main(), parent);
}
}
}

