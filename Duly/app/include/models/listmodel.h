#ifndef LISTMODEL_H
#define LISTMODEL_H


#include <QAbstractListModel>

namespace duly_gui {
    namespace models {
        template<class T>
        class ListModel: public QAbstractListModel
        {
            Q_OBJECT
        public:
            ListModel(QObject *parent = nullptr): QAbstractListModel(parent) {}
            ListModel(QList<T*> list, QObject *parent = nullptr) : QAbstractListModel(parent), m_list(list) {}

            QList<T *> list() const { return m_list; }
            void setList(const QList<T *> &list) {m_list = list;}

        private:
            QList<T*> m_list;

        public:
            int rowCount(const QModelIndex &parent) const
            {
                if (parent.isValid()) {
                    return 0;
                }
                return m_list.count();
            }
            QVariant data(const QModelIndex &index, int role) const
            {
                if (index.row() < 0 || index.row() >= m_list.size()) {
                    return QVariant();
                }
                if (role == Qt::DisplayRole || role == Qt::EditRole) {
                    return m_list.at(index.row());
                }
                return QVariant();
            }
        };
    }
}

#endif // LISTMODEL_H
