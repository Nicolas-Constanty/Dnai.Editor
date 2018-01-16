#include <QDebug>
#include "models/namespacebarmodel.h"

NameSpaceBarModel::NameSpaceBarModel(QList<NameSpaceBarItem *> list, QObject *parent)
    : QAbstractListModel(parent)
{
     qDebug() << "yolo";
    for (auto i = 0; i < list.size(); i++)
    {
        if (list[i] != nullptr)
        {
            QVariant var = QVariant::fromValue(list[i]);
            m_list.append(var);
        }
    }
}

int NameSpaceBarModel::rowCount(const QModelIndex &parent) const
{
    return m_list.size();
}

//int NameSpaceBarModel::columnCount(const QModelIndex &parent) const
//{

//}

QVariant NameSpaceBarModel::data(const QModelIndex &index, int role) const
{
    qDebug() << "yolo";
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_list.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        return  m_list.at(index.row());
    }
    return QVariant();
}
