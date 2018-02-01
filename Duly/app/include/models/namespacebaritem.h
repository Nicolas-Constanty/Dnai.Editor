#ifndef NAMESPACEBARITEM_H
#define NAMESPACEBARITEM_H

#include <QObject>
#include <QModelIndex>
#include "models/common.h"
#include "models/treeitem.h"

namespace duly_gui {
namespace models {
class NameSpaceBarItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY(bool asChild READ asChild WRITE setAsChild NOTIFY asChildChanged)
    Q_PROPERTY(QModelIndex idx READ idx WRITE setIdx NOTIFY idxChanged)
    Q_PROPERTY(duly_gui::models::TreeItem * model READ model WRITE setModel NOTIFY modelChanged)
public:
    NameSpaceBarItem(QObject *parent = 0) : QObject(parent) {}

signals:
    void pathChanged(const QString &);
    void asChildChanged(bool changed);
    void idxChanged(const QModelIndex &idx);
    void modelChanged(duly_gui::models::TreeItem *m);

public:
    QString path() const { return m_path; }
    void setPath(const QString &s);
    bool asChild() const { return m_asChild; }
    void setAsChild(bool b);
    QModelIndex idx() const { return m_idx; }
    void setIdx(const QModelIndex &idx);

    void setModel(duly_gui::models::TreeItem *model);
    duly_gui::models::TreeItem *model() const { return m_model; }
private:
    QString m_path;
    bool m_asChild;
    QModelIndex m_idx;
    duly_gui::models::TreeItem *m_model;
};

}
}

#endif // NAMESPACEBARITEM_H