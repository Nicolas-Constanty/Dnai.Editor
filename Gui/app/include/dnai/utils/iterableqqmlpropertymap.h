#ifndef DNAI_UTILS_ITERABLE_QQMLPROPERTYMAP_H
#define DNAI_UTILS_ITERABLE_QQMLPROPERTYMAP_H

#include <QQmlPropertyMap>
#include <QAbstractListModel>

namespace dnai {
namespace utils {
class IterableQQmlPropertyMap : public QAbstractListModel
{
    Q_OBJECT
public:
    IterableQQmlPropertyMap(QObject *parent = nullptr);

    // QAbstractItemModel interface
public:
    enum ROLES
    {
        OBJ = Qt::UserRole + 1,
        KEY
    };

    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;

    QVariant value(const QString &key) const;
    void insert(const QString &key, const QVariant &value);
    void clear(const QString &key);

    Q_INVOKABLE QStringList keys() const;

    int count() const;
    int size() const;
    bool isEmpty() const;
    bool contains(const QString &key) const;

    QVariant &operator[](const QString &key);
    QVariant operator[](const QString &key) const;

private:
    virtual QHash<int, QByteArray> roleNames() const override;

signals:
    void valueChanged(const QString &key, const QVariant &value);

private:
    QQmlPropertyMap m_map;
};
}
}

#endif // DNAI_UTILS_ITERABLE_QQMLPROPERTYMAP_H
