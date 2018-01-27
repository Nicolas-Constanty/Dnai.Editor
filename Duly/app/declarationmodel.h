#ifndef DECLARATIONMODEL_H
#define DECLARATIONMODEL_H

#include <QAbstractListModel>
#include "models/common.h"

class Declaration : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        ItemRole = Qt::UserRole + 1,
    };
    Declaration(QObject *parent= nullptr) : QAbstractListModel(parent), m_name("Test"), m_comment("This is a comment") {}
    void addModel(duly_gui::models::Common *c);
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    void setName(const QString &n);
    const QString &name() const { return m_name; }
    void setComment(const QString &n);
    const QString &comment() const { return m_comment; }


protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<duly_gui::models::Common *> m_model;
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
        ItemRole
    };
    DeclarationModel(QObject *parent= nullptr) : QAbstractListModel(parent) {}
    void addDeclaration(Declaration *c);
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<Declaration *> m_model;
};


//class DeclarationModel : public QObject
//{
//    Q_OBJECT
//    Q_PROPERTY(QList<duly_gui::models::Common *> md READ md WRITE setMd NOTIFY mdChanged)
//    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
//    Q_PROPERTY(QString comment READ comment WRITE setComment NOTIFY commentChanged)

//public:
//    DeclarationModel(QObject *parent = nullptr) : QObject(parent), m_name("The name"), m_comment("The super comment") {}

//signals:
//    void mdChanged(const QList<duly_gui::models::Common *> m);
//    void nameChanged(const QString &n);
//    void commentChanged(const QString &c);

//public:
//    void add(duly_gui::models::Common *);
//    void setMd(const QList<duly_gui::models::Common *> m);
//    const QList<duly_gui::models::Common *> &md() const { return m_model; }
//    void setName(const QString &n);
//    const QString &name() const { return m_name; }
//    void setComment(const QString &n);
//    const QString &comment() const { return m_comment; }


//private:
//    QList<duly_gui::models::Common *> m_model;
//    QString m_name;
//    QString m_comment;
//};

#endif // DECLARATIONMODEL_H
