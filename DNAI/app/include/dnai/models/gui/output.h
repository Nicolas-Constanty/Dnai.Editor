#ifndef DNAI_MODELS_GUI_OUTPUT_H
#define DNAI_MODELS_GUI_OUTPUT_H

#include "dnai/interfaces/iserializable.h"
#include "data/output.h"
#include "dnai/interfaces/imodeldata.h"
#include "dnai/interfaces/ivariable.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
            class Output : public interfaces::IVariable, public interfaces::IModelData<data::Output>, public interfaces::ASerializable<Output>
			{
			public:
				void serialize(QJsonObject& obj) const override;
			protected:
				void _deserialize(const QJsonObject& obj) override;
            public:
	            const data::Output& data() const override;
	            bool setData(const data::Output& data) override;
	            qint32 varType() const override;
	            bool setVarType(qint32 id) override;
	            const QJsonObject &value() const override;
	            bool setValue(const QJsonObject& value) override;
            private:
				data::Output m_data;
			};
		}
	}
}

#endif //DNAI_MODELS_GUI_OUTPUT_H
