#ifndef DNAI_MODELS_GUI_OUTPUT_H
#define DNAI_MODELS_GUI_OUTPUT_H

#include "dnai/interfaces/iserializable.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
            class Output : public interfaces::ASerializable<Output>
			{
			public:
				void serialize(QJsonObject& obj) const override;
			protected:
				void _deserialize(const QJsonObject& obj) override;
			};
		}
	}
}

#endif //DNAI_MODELS_GUI_OUTPUT_H
