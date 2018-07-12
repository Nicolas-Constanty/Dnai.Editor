#ifndef DNAI_MODELS_ENTITY_TREE_H
#define DNAI_MODELS_ENTITY_TREE_H

#include <QAbstractListModel>
#include "entity.h"
#include "dnai/interfaces/iserializable.h"

namespace dnai
{
	namespace models
	{
        class EntityTree : public QAbstractItemModel
		{
			Q_OBJECT
		
		public:
			enum ROLES
			{
				ID = Qt::UserRole + 1,
				TYPE,
				CONTAINER_ID,
				NAME,
				VISIBILITY,
				INDEX,
				LISTINDEX,
				DESCRIPTION,
				CORE_MODEL,
				GUI_MODEL,
				MODEL,
				EXPANDED,
				LIST_COLUMN
			};

		// QAbstractItemModel implementation
		public:
            EntityTree(QObject *parent = nullptr);
			QModelIndex index(int row, int column, const QModelIndex& parent) const override;
			QModelIndex parent(const QModelIndex& child) const override;
			int rowCount(const QModelIndex& parent) const override;
			int columnCount(const QModelIndex& parent) const override;
			QVariant data(const QModelIndex& index, int role) const override;
            Q_INVOKABLE int getRoleKey(QString rolename) const;

        protected:
            Entity * getItem(const QModelIndex& index) const;
            QHash<int, QByteArray> roleNames() const override;
			Entity *m_rootItem;
		};
	}
}

#endif //DNAI_MODELS_ENTITY_TREE_H
