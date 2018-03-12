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
				class EnumType : public interfaces::IEntity, public interfaces::IModelData<data::EnumType>, public interfaces::ASerializable<EnumType>
				{

				public:
					explicit EnumType();
					//Implementation of ISerializable
					void serialize(QJsonObject& obj) const override;
				protected:
					void _deserialize(const QJsonObject& obj) override;
					//Implementation of IModelData
				public:
					const data::EnumType& data() const override;
					bool setData(const data::EnumType& data) override;
				public:
					int index() const override;
					bool setIndex(int index) override;
					int listIndex() const override;
					bool setListIndex(int listIndex) override;
					const QString& description() const override;
					bool setDescription(const QString& description) override;

				protected:
					data::EnumType m_data;
				};
			}
		}
	}
}

#endif //DNAI_MODELS_DECLARABLE_CONTEXT_H