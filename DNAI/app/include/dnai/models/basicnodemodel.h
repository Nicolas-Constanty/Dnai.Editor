#ifndef BASICNODEMODEL_H
#define BASICNODEMODEL_H

#include <QMap>
#include <QQmlComponent>
#include "listnode.h"
#include "dnai/enums/core/instructionid.h"

namespace dnai {
	namespace models {
		class BasicNodeModel : public QAbstractListModel
		{
			Q_OBJECT
		public:
			enum NodeCategories
			{
				NODE_MODELS = Qt::UserRole + 1,
                NAME
			};
			explicit BasicNodeModel(QObject *parent = nullptr);
			int rowCount(const QModelIndex&) const override;
			QVariant data(const QModelIndex& index, int role) const override;
            QObject *createNode(enums::QInstructionID::Instruction_ID nodeId) const;
            ~BasicNodeModel();
		protected:
			QHash<int, QByteArray> roleNames() const override;

		private:
			void loadCurrentModel();
			void instantiateComponents();
			void instantiateComponent(const QString &category, const QString &path);
			void setQmlPaths(const QString &path);

		private:
			QMap<QString, QStringList> m_qmlpaths;
			QMap<QString, ListNode*> m_nodes;
            QMap<enums::QInstructionID::Instruction_ID, QQmlComponent *> m_components;
		};
	}
}

#endif // BASICNODEMODEL_H
