#ifndef DNAI_MODELS_DECLARABLE_CONTEXT_H
#define DNAI_MODELS_DECLARABLE_CONTEXT_H

#include "dnai/models/gui/data/context.h"
#include "entity.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			namespace declarable
			{
				class Context : public Entity<data::Context, Context>
				{
				public:
					explicit Context() = default;
					//Implementation of ISerializable
					void serialize(QJsonObject& obj) const override;
				protected:
					virtual void _deserialize(const QJsonObject& obj) override;
				};
			}
		}
	}
}

#endif //DNAI_MODELS_DECLARABLE_CONTEXT_H