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

				signals:
                    void varTypeChanged(QUuid id);
					void valueChanged(const QString &variant);

                private:
					static EntityList *m_variables;
				};
			}
		}
	}
}

#endif //DNAI_MODELS_DECLARABLE_VARIABLE_H
