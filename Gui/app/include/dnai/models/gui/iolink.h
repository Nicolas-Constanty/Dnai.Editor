#ifndef DNAI_MODELS_GUI_IOLINK
#define DNAI_MODELS_GUI_IOLINK
#include "dnai/interfaces/imodeldata.h"
#include "dnai/interfaces/iserializable.h"
#include "data/iolink.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			class IoLink : public interfaces::IModelData<data::IoLink>, public interfaces::ASerializable<IoLink>
			{
			public:
				const data::IoLink& data() const override;
				bool setData(const data::IoLink& data) override;
				void serialize(QJsonObject& obj) const override;
			protected:
				void _deserialize(const QJsonObject& obj) override;
			private:
				data::IoLink m_data;
			};
		}
	}
}

#endif //DNAI_MODELS_GUI_IOLINK
