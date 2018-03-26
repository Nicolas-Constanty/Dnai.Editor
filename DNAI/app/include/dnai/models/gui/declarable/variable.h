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
                class Variable : public interfaces::IVariable, public Entity<data::Variable, Variable>
                {
				public:
					explicit Variable() = default;
                    //Implementation of ISerializable
					void serialize(QJsonObject& obj) const override;
				protected:
					void _deserialize(const QJsonObject& obj) override;
				public:
	                qint32 varType() const override;
	                bool setVarType(qint32 id) override;
	                const QJsonObject &value() const override;
	                bool setValue(const QJsonObject& value) override;
				};
			}
		}
	}
}

#endif //DNAI_MODELS_DECLARABLE_VARIABLE_H
