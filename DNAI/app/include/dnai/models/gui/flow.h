#ifndef DNAI_MODELS_GUI_FLOW_H
#define DNAI_MODELS_GUI_FLOW_H

#include "dnai/interfaces/imodeldata.h"
#include "dnai/interfaces/iserializable.h"
#include "data/flow.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			class Flow : public interfaces::IModelData<data::Flow>, public interfaces::ASerializable<Flow>
			{
			public:
				void serialize(QJsonObject& obj) const override;
			protected:
				void _deserialize(const QJsonObject& obj) override;
			public:
				const data::Flow& data() const override;
				bool setData(const data::Flow& data) override;

				Flow &operator=(const Flow &link) = default;
				bool operator!=(const Flow &link) const
				{
					return !(*this == link);
				}
				bool operator==(const Flow &link) const
				{
					return (link.data() == m_data);
				}
			private:
				data::Flow m_data;
			};
		}
	}
}

#endif //DNAI_MODELS_GUI_FLOW_H