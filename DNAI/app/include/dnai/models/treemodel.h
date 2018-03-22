#ifndef DNAI_MODELS_TREEMODEL_H
#define DNAI_MODELS_TREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include "dnai/project.h"

namespace dnai
{
	namespace models
	{
		class TreeItem;

		class TreeModel : public QAbstractItemModel
		{
			Q_OBJECT

		public:
			TreeModel(const QStringList &headers, const QString &data,
				QObject *parent = 0);
			~TreeModel();

			QVariant data(const QModelIndex &index, int role) const override;
			QVariant headerData(int section, Qt::Orientation orientation,
				int role = Qt::DisplayRole) const override;

			QModelIndex index(int row, int column,
				const QModelIndex &parent = QModelIndex()) const override;
			QModelIndex parent(const QModelIndex &index) const override;

			int rowCount(const QModelIndex &parent = QModelIndex()) const override;
			int columnCount(const QModelIndex &parent = QModelIndex()) const override;

			Qt::ItemFlags flags(const QModelIndex &index) const override;
			bool setData(const QModelIndex &index, const QVariant &value,
				int role = Qt::EditRole) override;
			bool setHeaderData(int section, Qt::Orientation orientation,
				const QVariant &value, int role = Qt::EditRole) override;
			virtual void setupModelData(const QJsonObject& obj, TreeItem* parent) = 0;

			bool insertColumns(int position, int columns,
				const QModelIndex &parent = QModelIndex()) override;
			bool removeColumns(int position, int columns,
				const QModelIndex &parent = QModelIndex()) override;
			bool insertRows(int position, int rows,
				const QModelIndex &parent = QModelIndex()) override;
			bool removeRows(int position, int rows,
				const QModelIndex &parent = QModelIndex()) override;

		protected:
			TreeItem *getItem(const QModelIndex &index) const;
			TreeItem *m_rootItem;
		};

	}
}

#endif // DNAI_MODELS_TREEMODEL_H
