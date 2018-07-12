#ifndef DNAI_MODELS_GUI_ENTITYLIST_H
#define DNAI_MODELS_GUI_ENTITYLIST_H

#include <QAbstractListModel>

namespace dnai
{
	namespace models
	{
        class Entity;
		namespace gui
		{
			class EntityList : public QAbstractListModel
			{
				Q_OBJECT

			public:
				EntityList(QObject *parent = nullptr) : QAbstractListModel(parent), m_list(nullptr)
				{
				}
				enum Roles {
					Name = Qt::UserRole + 1,
					Type,
					Entity
				};
				explicit EntityList(QList<models::Entity*> *);
				explicit EntityList(const QList<models::Entity*> &);
				int rowCount(const QModelIndex& parent) const override;
				QVariant data(const QModelIndex& index, int role) const override;
				void append(models::Entity *var);
				void moveUp(int index);
				void moveDown(int index);
				void remove(const QString &name);

				bool setData(const QModelIndex& index, const QVariant& value, int role) override;
				bool setData(int index, const QVariant& value, int role);

			private:
				QList<models::Entity*> *m_list;
				QHash<int, QByteArray> roleNames() const override;
			};
		}
	}
}

#endif
