#include <QDebug>
#include <algorithm>
#include "declarationmodel.h"

//void DeclarationModel::add(duly_gui::models::Common *m)
//{
//    m_model.append(m);
//    emit mdChanged(m_model);
//}

//void DeclarationModel::setMd(const QList<duly_gui::models::Common *> m)
//{
//    m_model = m;
//    emit mdChanged(m_model);
//}

//void DeclarationModel::setName(const QString &n)
//{
//    if (n == m_name)
//        return;
//    m_name = n;
//    emit nameChanged(n);
//}

//void DeclarationModel::setComment(const QString &n)
//{
//    if (n == m_comment)
//        return;
//    m_comment = n;
//    emit commentChanged(n);
//}

void Declaration::addModel(duly_gui::models::Common *c)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_model << c;
    endInsertRows();
}

int Declaration::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_model.count();
}

QVariant Declaration::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_model.count())
        return QVariant();

    auto item = m_model[index.row()];
    if (role == ItemRole)
        return QVariant::fromValue(item);
    else if (role == Qt::DisplayRole)
        return QVariant::fromValue(item);

    return QVariant();
}

bool Declaration::removeRow(int row, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    beginRemoveRows(QModelIndex(), row, row);
    m_model.removeAt(row);
    endRemoveRows();
    return true;
}

void Declaration::removeSelectedItem(int count)
{
    while (count > 0)
    {
        for (auto i = 0; i < m_model.size(); i++)
        {
            if (m_model[i] && m_model[i]->isSelect())
            {
                removeRow(i);
                count -= 1;
                break;
            }
        }
    }
}

void Declaration::setName(const QString &n)
{
    if (n == m_name)
        return;
    m_name = n;
}

void Declaration::setComment(const QString &n)
{
    if (n == m_comment)
        return;
    m_comment = n;
}

QHash<int, QByteArray> Declaration::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ItemRole] = "item";
    return roles;
}


void DeclarationModel::addDeclaration(Declaration *c)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_model << c;
    endInsertRows();
}

int DeclarationModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_model.count();
}


void DeclarationModel::setIsContext(bool value)
{
    m_isContext = value;
}

QVariant DeclarationModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_model.count())
        return QVariant();

    auto item = m_model[index.row()];
    if (role == Qt::DisplayRole)
        return QVariant::fromValue(item);
    else if (role == NameRole)
        return item->name();
    else if (role == CommentRole)
        return item->comment();
    else if (role == ItemRole)
        return QVariant::fromValue(item);
    else if (role == IsContextRole)
        return m_isContext;
    return QVariant();
}

void DeclarationModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, rowCount());
    m_model.clear();
    endRemoveRows();
}


QHash<int, QByteArray> DeclarationModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[CommentRole] = "comment";
    roles[ItemRole] = "item";
    roles[IsContextRole] = "isContext";
    return roles;
}
