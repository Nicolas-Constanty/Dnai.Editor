#ifndef DNAI_MODELS_GUI_FLOW_H
#define DNAI_MODELS_GUI_FLOW_H

#include "dnai/interfaces/iserializable.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			class Flow : public interfaces::ASerializable<Flow>
			{
			public:
				void serialize(QJsonObject& obj) const override;
			protected:
				void _deserialize(const QJsonObject& obj) override;
			};
		}
	}
}

#endif //DNAI_MODELS_GUI_FLOW_H