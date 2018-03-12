#ifndef DNAI_MODELS_DECLARABLE_OBJECTTYPE_H
#define DNAI_MODELS_DECLARABLE_OBJECTTYPE_H

#include "dnai/models/gui/data/objecttype.h"
#include "entity.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			namespace declarable
			{
				class ObjectType : public interfaces::IEntity, public interfaces::IModelData<data::ObjectType>, public interfaces::ASerializable<ObjectType>
				{
				public:
					explicit ObjectType();
					//Implementation of ISerializable
					void serialize(QJsonObject& obj) const override;
				protected:
					void _deserialize(const QJsonObject& obj) override;
					//Implementation of IModelData
				public:
					const data::ObjectType& data() const override;
					bool setData(const data::ObjectType& data) override;
				public:
					int index() const override;
					bool setIndex(int index) override;
					int listIndex() const override;
					bool setListIndex(int listIndex) override;
					const QString& description() const override;
					bool setDescription(const QString& description) override;

				protected:
					data::ObjectType m_data;
				};
			}
		}
	}
}

#endif //DNAI_MODELS_DECLARABLE_OBJECTTYPE_H