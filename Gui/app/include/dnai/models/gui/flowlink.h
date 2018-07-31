#ifndef DNAI_MODELS_GUI_FLOWLINK
#define DNAI_MODELS_GUI_FLOWLINK

#include "dnai/interfaces/imodeldata.h"
#include "data/flowlink.h"
#include "dnai/interfaces/iserializable.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
            class FlowLink : public interfaces::IModelData<data::FlowLink>, public interfaces::ASerializable<FlowLink>
			{
			public:
				const data::FlowLink& data() const override;
				bool setData(const data::FlowLink& data) override;
				void serialize(QJsonObject& obj) const override;

			protected:
				void _deserialize(const QJsonObject& obj) override;
			private:
				data::FlowLink m_data;
			};
		}
	}
}

#endif //DNAI_MODELS_GUI_FLOWLINK
