#ifndef DNAI_MODELS_DECLARABLE_VARIABLE_H
#define DNAI_MODELS_DECLARABLE_VARIABLE_H

#include <QObject>
#include "dnai/interfaces/ivariable.h"
#include "dnai/models/gui/data/variable.h"
#include "entity.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			namespace declarable
			{
                class Variable : public QObject, public interfaces::IVariable, public Entity<data::Variable, Variable>
                {
					Q_OBJECT
					Q_PROPERTY(qint32 varType READ varType WRITE setVarType NOTIFY varTypeChanged)
					Q_PROPERTY(QString value READ value WRITE setValue NOTIFY valueChanged)

				public:
					explicit Variable(QObject *parent = nullptr);
                    //Implementation of ISerializable
					void serialize(QJsonObject& obj) const override;
				protected:
					void _deserialize(const QJsonObject& obj) override;
				public:
                    qint32 varType() const override;
                    bool setVarType(qint32 id) override;
	                const QString &value() const override;
	                bool setValue(const QString& value) override;

					static const QString &getVariableName(qint32 identifier);
					static void addVariableType(qint32 identifier, const QString &name);
	                static const QMap<qint32, QString>& getVariableMap();
	                static const QStringList &getVariableList();
					static const int variableListCount();

				signals:
					void varTypeChanged(qint32 id);
					void valueChanged(const QString &variant);


                private:
					static QMap<qint32, QString> m_typeMap;
					static QStringList m_typeList;
				};
			}
		}
	}
}

#endif //DNAI_MODELS_DECLARABLE_VARIABLE_H
