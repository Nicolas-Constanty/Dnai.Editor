#include <QDebug>

#include "dnai/utils/iterableqqmlpropertymap.h"

namespace dnai {
namespace utils {

IterableQQmlPropertyMap::IterableQQmlPropertyMap(QObject *parent) : QAbstractListModel(parent)
{
    QObject::connect(&m_map, SIGNAL(valueChanged(const QString &, const QVariant &)),
                     this, SIGNAL(valueChanged(const QString &, const QVariant &)));
}

int IterableQQmlPropertyMap::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_map.count();
}

QVariant IterableQQmlPropertyMap::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (role == ROLES::OBJ)
        return QVariant::fromValue( m_map[m_map.keys().at(index.row())] );
    else if (role == ROLES::KEY)
        return QVariant::fromValue( m_map.keys().at(index.row()) );
    return QVariant();
}

QVariant IterableQQmlPropertyMap::value(const QString &key) const
{
    return m_map.value(key);
}

void IterableQQmlPropertyMap::insert(const QString &key, const QVariant &value)
{
    return m_map.insert(key, value);
}

void IterableQQmlPropertyMap::clear(const QString &key)
{
    return m_map.clear(key);
}

QStringList IterableQQmlPropertyMap::keys() const
{
    return m_map.keys();
}

int IterableQQmlPropertyMap::count() const
{
    return m_map.count();
}

int IterableQQmlPropertyMap::size() const
{
    return m_map.size();
}

bool IterableQQmlPropertyMap::isEmpty() const
{
    return m_map.isEmpty();
}

bool IterableQQmlPropertyMap::contains(const QString &key) const
{
    return m_map.contains(key);
}

QVariant &IterableQQmlPropertyMap::operator[](const QString &key)
{
    return m_map.operator [](key);
}

QVariant IterableQQmlPropertyMap::operator[](const QString &key) const
{
    return m_map.operator [](key);
}

QHash<int, QByteArray> IterableQQmlPropertyMap::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ROLES::OBJ] = "obj";
    roles[ROLES::KEY] = "key";
    return roles;
}

}
}
