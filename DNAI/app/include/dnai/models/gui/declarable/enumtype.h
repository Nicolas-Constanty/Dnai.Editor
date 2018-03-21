#ifndef DNAI_MODELS_DECLARABLE_ENUMTYPE_H
#define DNAI_MODELS_DECLARABLE_ENUMTYPE_H

#include "dnai/models/gui/data/enumtype.h"
#include "entity.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			namespace declarable
			{
				class EnumType : public Entity<data::EnumType, EnumType>
				{

				public:
					explicit EnumType() = default;
					//Implementation of ISerializable
					void serialize(QJsonObject& obj) const override;
				protected:
					void _deserialize(const QJsonObject& obj) override;
				};
			}
		}
	}
}

#endif //DNAI_MODELS_DECLARABLE_CONTEXT_H