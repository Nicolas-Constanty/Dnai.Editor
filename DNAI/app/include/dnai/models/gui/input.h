#ifndef DNAI_MODELS_GUI_INPUT_H
#define DNAI_MODELS_GUI_INPUT_H

#include "dnai/interfaces/iserializable.h"

class QJsonObject;

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			class Input : public interfaces::ASerializable<Input>
			{
			public:
				void serialize(QJsonObject& obj) const override;
			protected:
				void _deserialize(const QJsonObject& obj) override;
			};
		}
	}
}

#endif //DNAI_MODELS_GUI_INPUT_H