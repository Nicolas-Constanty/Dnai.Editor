#include "declarationcolumnmodel.h"

DeclarationColumnModel::DeclarationColumnModel(QObject *parent) :  QAbstractListModel (parent)
{

}

void DeclarationColumnModel::add(DeclarationModel *m)
{
    m_model.append(m);
    emit mdChanged(m_model);
}

void DeclarationColumnModel::setMd(const QList<DeclarationModel *> m)
{
    m_model = m;
    emit mdChanged(m_model);
}

int DeclarationColumnModel::count()
{
    return m_model.size();
}

int DeclarationColumnModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_model.size();
}

QVariant DeclarationColumnModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
            return QVariant();

    if (index.row() >= m_model.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        return QVariant::fromValue(m_model.at(index.row()));
    }
    return QVariant();
}
