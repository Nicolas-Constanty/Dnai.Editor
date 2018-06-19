#ifndef DNAI_MODELS_DECLARABLE_VARIABLE_H
#define DNAI_MODELS_DECLARABLE_VARIABLE_H

#include <QObject>
#include "dnai/interfaces/ivariable.h"
#include "dnai/models/gui/data/variable.h"
#include "dnai/models/gui/declarable/entity.h"
#include <QAbstractListModel>

namespace dnai
{
	namespace models
	{
		namespace gui
		{
            class EntityList;
			namespace declarable
			{
				class VarTypeList : public QAbstractListModel
				{
					Q_OBJECT
				public:
					enum Roles {
						Name = Qt::UserRole + 1,
						Type
					};
					int rowCount(const QModelIndex& parent) const override;
					void append(const QString& name, quint32);
					void append(const QPair<QString, quint32>& value);
					void remove(const QString &name);
					QVariant data(const QModelIndex& index, int role) const override;

					Q_INVOKABLE QString getNameFromValue(quint32 value);
					Q_INVOKABLE int getIndexFromValue(quint32 value);
					Q_INVOKABLE int getValueFromIndex(int value) const;
					Q_INVOKABLE const QVariant &names();

				private:
					QMap<QString, quint32> m_values;
					QVariant m_keys;
					QHash<int, QByteArray> roleNames() const override;
				};
                class Variable : public QObject, public interfaces::IVariable, public Entity<data::Variable, Variable>
                {
					Q_OBJECT
                    Q_PROPERTY(QUuid varType READ varType WRITE setVarType NOTIFY varTypeChanged)
					Q_PROPERTY(QString value READ value WRITE setValue NOTIFY valueChanged)

				public:
					explicit Variable(QObject *parent = nullptr);
                    //Implementation of ISerializable
					void serialize(QJsonObject& obj) const override;
				protected:
					void _deserialize(const QJsonObject& obj) override;
				public:
                    QUuid varType() const override;
                    bool setVarType(QUuid const &id) override;
	                const QString &value() const override;
	                bool setValue(const QString& value) override;

					static EntityList *variables();
					static VarTypeList *varTypes();

				signals:
                    void varTypeChanged(QUuid id);
					void valueChanged(const QString &variant);

                private:
					static VarTypeList *m_varTypes;
					static EntityList *m_variables;
				};
			}
		}
	}
}

#endif //DNAI_MODELS_DECLARABLE_VARIABLE_H
