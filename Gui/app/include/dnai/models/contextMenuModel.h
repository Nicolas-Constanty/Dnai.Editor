#ifndef DNAI_MODELS_CONTEXT_MENU_MODEL_H
#define DNAI_MODELS_CONTEXT_MENU_MODEL_H
#include <QAbstractItemModel>
#include <QHash>
#include <QStringList>
#include "generictreeitem.h"

namespace dnai
{
	namespace models
	{
        class Entity;
		class ContextMenuItem : public GenericTreeItem<ContextMenuItem>
		{
			Q_OBJECT
			Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
			Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
			Q_PROPERTY(int inputs READ inputs WRITE setInputs NOTIFY inputsChanged)
			Q_PROPERTY(int outputs READ outputs WRITE setOutputs NOTIFY outputsChanged)
			Q_PROPERTY(int instructionId READ instructionId WRITE setInstructionId NOTIFY instructionIdChanged)
			Q_PROPERTY(QString nodeName READ nodeName WRITE setNodeName NOTIFY nodeNameChanged)
            Q_PROPERTY(int type READ type WRITE setType NOTIFY typeChanged)
            Q_PROPERTY(QList<qint32> construction READ construction WRITE setConstruction NOTIFY constructionChanged)
            Q_PROPERTY(int flowIn READ flowIn WRITE setFlowIn NOTIFY flowInChanged)
            Q_PROPERTY(int flowOut READ flowOut WRITE setFlowOut NOTIFY flowOutChanged)
			Q_PROPERTY(QStringList inputNames READ inputNames WRITE setInputNames NOTIFY inputNamesChanged)
			Q_PROPERTY(QStringList outputNames READ outputNames WRITE setOutputNames NOTIFY outputNamesChanged)

		public:
			const QString &name() const;
			const QString &description() const;
			int inputs() const;
			int outputs() const;
			int instructionId() const;
			const QString &nodeName() const;
			int columnCount() const override;
            int type() const;
            QList<qint32> const &construction() const;
            int flowIn() const;
            int flowOut() const;
			const QStringList &inputNames() const;
			const QStringList &outputNames() const;
			void appendInputName(const QString &name);
			void appendOutputName(const QString &name);

		public:
			void setName(const QString &);
			void setDescription(const QString &);
			void setInputs(int);
			void setOutputs(int);
			void setInstructionId(int);
			void setNodeName(const QString &name);
            void setType(int t);
            void setConstruction(QList<qint32> const &value);
            void setFlowIn(int value);
            void setFlowOut(int value);
			void setInputNames(const QStringList &value);
			void setOutputNames(const QStringList &value);

		signals:
			void nameChanged(const QString &);
			void descriptionChanged(const QString &);
			void inputsChanged(int);
			void outputsChanged(int);
			void instructionIdChanged(int);
			void nodeNameChanged(const QString &name);
            void typeChanged(int t);
            void constructionChanged(QList<qint32> const &value);
            void flowInChanged(int value);
            void flowOutChanged(int value);
			void inputNamesChanged(const QStringList &value);
			void outputNamesChanged(const QStringList &value);

		private:
			QString m_name;
			QString m_descrition;
			int m_inputs = 0;
			int m_outputs = 0;
			int m_instructionId = 0;
			QString m_nodeName;
            int m_type = -1;
            QList<qint32> m_construction;
			int m_flowIn = 0;
			int m_flowOut = 0;
			QStringList m_inputNames;
			QStringList m_outputNames;
		};
		class ContextMenuModel : public QAbstractItemModel
		{
			Q_OBJECT
		public:
			enum ROLES
			{
				NAME = Qt::UserRole + 1,
				ITEM,
				DESCRIPTION,
				INPUTS,
                OUTPUTS,
                CONSTRUCTION,
                INSTRUCTION_ID
			};

		public:
			explicit ContextMenuModel(QObject *parent = nullptr);
			explicit ContextMenuModel(const QJsonObject &doc, QObject *parent = nullptr);

			QModelIndex index(int row, int column, const QModelIndex& parent) const override;
			QModelIndex parent(const QModelIndex& child) const override;
			ContextMenuItem* getItem(const QModelIndex& index) const;
			int rowCount(const QModelIndex& parent) const override;
			int columnCount(const QModelIndex& parent) const override;
			QVariant data(const QModelIndex& index, int role) const override;
            QHash<int, QByteArray> roleNames() const override;

            const QHash<int, ContextMenuItem*> &instructions() const;
            void appendVariable(Entity *entity);

		private:
			void parseJsonDocument(const QJsonObject &json);
			void parseJsonObj(ContextMenuItem* parent, const QJsonObject& js);
			ContextMenuItem *m_root;
            ContextMenuItem *m_variableGetter;
            ContextMenuItem *m_variableSetter;
            QHash<int, ContextMenuItem*> m_hash;
		};
	}
}

#endif //DNAI_MODELS_CONTEXT_MENU_MODEL_H