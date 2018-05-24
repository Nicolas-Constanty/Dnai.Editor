#ifndef DNAI_MODELS_GUI_INPUT_H
#define DNAI_MODELS_GUI_INPUT_H

#include "dnai/interfaces/imodeldata.h"
#include "dnai/interfaces/iserializable.h"
#include "dnai/interfaces/ivariable.h"
#include "data/input.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			class Input : public interfaces::IVariable, public interfaces::IModelData<data::Input>, public interfaces::ASerializable<Input>
			{
			public:
				void serialize(QJsonObject& obj) const override;
			protected:
				void _deserialize(const QJsonObject& obj) override;
			public:
				const data::Input& data() const override;
				bool setData(const data::Input& data) override;
                qint32 varType() const override;
                bool setVarType(qint32 id) override;
				const QJsonObject &value() const override;
				bool setValue(const QJsonObject& value) override;
			private:
				data::Input m_data;
			};
		}
	}
}

#endif //DNAI_MODELS_GUI_INPUT_H
