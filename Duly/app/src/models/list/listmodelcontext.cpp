#include "models/list/listmodelcontext.h"

namespace duly_gui {
    namespace models {
        ListModelContext::ListModelContext(QObject *parent)
            : QAbstractListModel(parent)
        {

        }

        ListModelContext::ListModelContext(QList<Context*> list, QObject *parent)
            : QAbstractListModel(parent), m_list(list) {

        }

        QList<Context *> ListModelContext::list() const
        {
            return m_list;
        }

        void ListModelContext::setList(const QList<Context *> &list)
        {
            m_list = list;
        }

        int ListModelContext::rowCount(const QModelIndex &parent) const
        {
            if (parent.isValid()) {
                return 0;
            }
            return m_list.count();
        }
        QVariant ListModelContext::data(const QModelIndex &index, int role) const
        {
            if (index.row() < 0 || index.row() >= m_list.size()) {
                return QVariant();
            }
            if (role == Qt::DisplayRole || role == Qt::EditRole) {
                return QVariant::fromValue<QObject *>(m_list.at(index.row()));
            }
            return QVariant();
        }
    }
}
