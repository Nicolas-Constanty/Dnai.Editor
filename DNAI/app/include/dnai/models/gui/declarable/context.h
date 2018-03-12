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
				class Context : public interfaces::IEntity, public interfaces::IModelData<data::Context>, public interfaces::ASerializable<Context>
				{
					
				public:
					explicit Context();
					//Implementation of ISerializable
					void serialize(QJsonObject& obj) const override;
				protected:
					void _deserialize(const QJsonObject& obj) override;
					//Implementation of IModelData
				public:
					const data::Context& data() const override;
					bool setData(const data::Context& data) override;
				public:
					int index() const override;
					bool setIndex(int index) override;
					int listIndex() const override;
					bool setListIndex(int listIndex) override;
					const QString& description() const override;
					bool setDescription(const QString& description) override;

				protected:
					data::Context m_data;
				};
			}
		}
	}
}

#endif //DNAI_MODELS_DECLARABLE_CONTEXT_H