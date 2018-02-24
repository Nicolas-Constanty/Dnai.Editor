#ifndef ENTITY_H
#define ENTITY_H

#include <QAbstractListModel>
#include "imodel.h"
#include "property.h"

namespace dnai {
namespace models {
	class Entity : public QAbstractListModel
	{
		Q_OBJECT
	public:
		enum Roles {
			ITEM_ROLE = Qt::UserRole + 1,
			NAME,
			VALUE
		};
		explicit Entity(QObject *parent = nullptr);
		explicit Entity(IModel *model, QObject *parent = nullptr);
		int rowCount(const QModelIndex & parent = QModelIndex()) const override;
		QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
		bool removeRow(int row, const QModelIndex &parent = QModelIndex());

	protected:
		void addModel(Property *c);
		QHash<int, QByteArray> roleNames() const override;

	private:
		QList<Property *> m_properties;
	};
}
}

#endif // ENTITY_H
