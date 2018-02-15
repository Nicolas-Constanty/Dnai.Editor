#include <QStringList>
#include <QDebug>

#include "dnai/models/treeitem.h"
#include "dnai/models/treemodel.h"

namespace dnai {
namespace models {
TreeModel::TreeModel(const Project *project, QObject *parent)
    : QAbstractItemModel(parent)
{
    QList<QVariant> rootData;
    rootData << "Name";
    rootItem = new TreeItem(rootData);
    rootItem->setIdx(index(0,0, QModelIndex()));
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

Common *TreeModel::matchModel(Common *c)
{
    return matchModelRecur(rootItem, c);
}

Common *TreeModel::matchModelRecur(TreeItem *ti, Common *c)
{
    if (ti->model() == c)
        return ti->model();
    for (auto i = 0; i < ti->children().count(); i++)
    {
        auto model = matchModelRecur(ti->children()[i], c);
        if (model)
            return model;
    }
    return nullptr;
}


QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole || role == NameRole)
    {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        return item->data(index.column());
    }
    if (role == ItemRole)
        return QVariant::fromValue(static_cast<TreeItem*>(index.internalPointer()));
    return QVariant();
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
    {
        return QModelIndex();
    }

    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
    {
        return createIndex(row, column, childItem);
    }
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

void TreeModel::setupContextModel(models::Context *context, TreeItem *parent, int currentIdx)
{
    QList<QVariant> columnData;
    columnData << context->name();

    auto modelidx = index(currentIdx, 0, parent->idxmodel());
    auto temp = new TreeItem(columnData, parent);
    parent->appendChild(temp);
    temp->setModel(static_cast<Common*>(context));
    temp->setIdx(modelidx);

    const auto contexts = context->contexts();
    for (auto i = 0; i < contexts.size(); i++)
        setupContextModel(contexts[i], temp, i);

    const auto classes = context->classes();
    for (auto i = 0; i < classes.size(); i++)
        setupClassModel(classes[i], temp, i);

    const auto functions = context->functions();
    for (auto i = 0; i < functions.size(); i++)
        setupFunctionModel(functions[i], temp, i);
}

void TreeModel::setupClassModel(models::Class *cl, TreeItem *parent, int currentIdx)
{
    QList<QVariant> columnData;
    columnData << cl->name();

    auto modelidx = index(currentIdx, 0, parent->idxmodel());
    auto temp = new TreeItem(columnData, parent);
    parent->appendChild(temp);
    temp->setModel(static_cast<Common*>(cl));
    temp->setIdx(modelidx);

    const auto classes = cl->classes();
    for (auto i = 0; i < classes.size(); i++)
        setupClassModel(classes[i], temp, i);

    const auto functions = cl->functions();
    for (auto i = 0; i < functions.size(); i++)
        setupFunctionModel(functions[i], temp, i);
}

void TreeModel::setupFunctionModel(models::Function *func, TreeItem *parent, int currentIdx)
{
    QList<QVariant> columnData;
    columnData << func->name();

    auto modelidx = index(currentIdx, 0, parent->idxmodel());
    auto temp = new TreeItem(columnData, parent);
    parent->appendChild(temp);
    temp->setModel(static_cast<Common*>(func));
    temp->setIdx(modelidx);
}

void TreeModel::setupModelData(const Project *project, TreeItem *parent)
{
    setupContextModel(const_cast<Context *>(project->main()), parent, 0);
}

QHash<int, QByteArray> TreeModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[ItemRole] = "item";
    return roles;
}

QModelIndexList TreeModel::match(const QModelIndex &start, int role, const QVariant &value, int hits, Qt::MatchFlags flags) const
{
    QModelIndexList result;
    uint matchType = flags & 0x0F;
    bool recurse = flags & Qt::MatchRecursive;
    bool wrap = flags & Qt::MatchWrap;
    bool allHits = (hits == -1);
    QString text; // only convert to a string if it is needed
    QModelIndex p = parent(start);
    int from = start.row();
    int to = rowCount(p);

    // iterates twice if wrapping
    for (int i = 0; (wrap && i < 2) || (!wrap && i < 1); ++i) {
        for (int r = from; (r < to) && (allHits || result.count() < hits); ++r) {
            QModelIndex idx = index(r, start.column(), p);
            if (!idx.isValid())
                continue;
            QVariant v = data(idx, role);
            // QVariant based matching
            if (matchType == Qt::MatchExactly) {
                if (value == v)
                    result.append(idx);
            } else {
                const auto t = qvariant_cast<TreeItem*>(v);
                if (t != nullptr && QVariant::fromValue(t->model()) == value)
                    result.append(idx);
            }
            if (recurse && hasChildren(idx)) { // search the hierarchy
                result += match(index(0, idx.column(), idx), role,
                                (text.isEmpty() ? value : text),
                                (allHits ? -1 : hits - result.count()), flags);
            }
        }
        // prepare for the next iteration
        from = 0;
        to = start.row();
    }
    return result;
}
}
}

