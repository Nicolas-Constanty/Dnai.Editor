#ifndef LISTMODELCONTEXT_H
#define LISTMODELCONTEXT_H


#include <QAbstractListModel>
#include "dnai/models/context.h"

namespace dnai {
    namespace models {
        class ListModelContext: public QAbstractListModel
        {
            Q_OBJECT
        public:
            ListModelContext(QObject * = nullptr);
            ListModelContext(QList<Context*>, QObject * = nullptr);

        private:
            QList<Context*> m_list;

        public:
            QList<Context *> list() const;
            void setList(const QList<Context *> &list);

        public:
            int rowCount(const QModelIndex &) const;
            QVariant data(const QModelIndex &, int ) const;
        };
    }
}

#endif // LISTMODELCONTEXT_H
