#include "dnai/models/listnode.h"

namespace dnai {
namespace models {

ListNode::ListNode(QObject* parent) : QAbstractListModel(parent)
{
}

ListNode::ListNode(const ListNode& other, QObject* parent) : QAbstractListModel(parent)
{
    *this = other;
}

int ListNode::rowCount(const QModelIndex&) const
{
    return m_nodes.count();
}

QVariant ListNode::data(const QModelIndex& index, int role) const
{
    if (role == Roles::ITEM)
        return QVariant::fromValue(m_nodes.at(index.row()));
    if (role == Roles::NAME)
        return m_nodes[index.row()]->property("name");
    if (role == Roles::INSTRUCTION_ID)
        return m_nodes[index.row()]->property("instruction_id");
    if (role == Roles::MENU_NAME)
        return m_nodes[index.row()]->property("menuName");
    return QVariant();
}

void ListNode::operator<<(QObject* value)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_nodes << value;
    endInsertRows();
}

ListNode& ListNode::operator=(const ListNode& other)
{
    for (auto i = 0; i < other.rowCount(); i++)
        m_nodes << other[i];
    return *this;
}

QObject* ListNode::operator[](const int i) const
{
    return m_nodes[i];
}

QHash<int, QByteArray> ListNode::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Roles::ITEM] = "item";
    roles[Roles::NAME] = "name";
    roles[Roles::INSTRUCTION_ID] = "instruction_id";
    roles[Roles::MENU_NAME] = "menuName";
    return roles;
}
}
}
