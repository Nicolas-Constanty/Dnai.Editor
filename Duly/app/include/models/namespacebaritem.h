#ifndef NAMESPACEBARITEM_H
#define NAMESPACEBARITEM_H

#include <QObject>
#include <QModelIndex>
#include "imodel.h"

namespace duly_gui {
namespace models {
class NameSpaceBarItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY(bool asChild READ asChild WRITE setAsChild NOTIFY asChildChanged)
    Q_PROPERTY(QModelIndex idx READ idx WRITE setIdx NOTIFY idxChanged)

public:
    NameSpaceBarItem(QObject *parent = 0) : QObject(parent) {}

signals:
    void pathChanged(const QString &);
    void asChildChanged(bool changed);
    void idxChanged(const QModelIndex &idx);

public:
    QString path() const { return m_path; }
    void setPath(const QString &s);
    bool asChild() const { return m_asChild; }
    void setAsChild(bool b);
    QModelIndex idx() const { return m_idx; }
    void setIdx(const QModelIndex &idx);
    void setModel(IModel *model);
    IModel *model() const { return m_model; }
private:
    QString m_path;
    bool m_asChild;
    QModelIndex m_idx;
    IModel *m_model;
};

}
}

#endif // NAMESPACEBARITEM_H
