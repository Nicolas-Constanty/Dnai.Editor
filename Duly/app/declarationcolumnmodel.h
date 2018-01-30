#ifndef DECLARATIONCOLUMNMODEL_H
#define DECLARATIONCOLUMNMODEL_H

#include <QAbstractListModel>
#include "declarationmodel.h"

class DeclarationColumnModel : public  QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QList<DeclarationModel *> md READ md WRITE setMd NOTIFY mdChanged)
public:
    explicit DeclarationColumnModel(QObject *parent = nullptr);

signals:
    void mdChanged(const QList<DeclarationModel *> m);

public:
    void add(DeclarationModel *);
    void setMd(QList<DeclarationModel *> m);
    const QList<DeclarationModel *> &md() const { return m_model; }
    int count();

private:
    QList<DeclarationModel *> m_model;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
};

#endif // DECLARATIONCOLUMNMODEL_H
