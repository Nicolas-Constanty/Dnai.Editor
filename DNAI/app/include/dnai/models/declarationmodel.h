#ifndef DECLARATIONMODEL_H
#define DECLARATIONMODEL_H

#include <QAbstractListModel>
#include "dnai/models/common.h"

namespace dnai {
namespace models {
class Declaration : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        ItemRole = Qt::UserRole + 1
    };
	explicit Declaration(QObject *parent= nullptr) : QAbstractListModel(parent), m_name("Title section"), m_comment("This is a comment") {}
    void addModel(dnai::models::Common *c);
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    bool removeRow(int row, const QModelIndex &parent = QModelIndex());
    void setName(const QString &n);
    const QString &name() const { return m_name; }
    void setComment(const QString &n);
    const QString &comment() const { return m_comment; }
    Q_INVOKABLE void removeSelectedItem(int count);

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<dnai::models::Common *> m_model;
    QString m_name;
    QString m_comment;
};

class DeclarationModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        NameRole = Qt::UserRole + 1,
        CommentRole,
        ItemRole,
        IsContextRole
    };

	explicit DeclarationModel(QObject *parent= nullptr) : QAbstractListModel(parent), m_isContext(true) {}
    void setIsContext(bool value);
    void addDeclaration(Declaration *c);
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    void clear();

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    bool m_isContext;
    QList<Declaration *> m_model;
};
}
}
#endif // DECLARATIONMODEL_H
