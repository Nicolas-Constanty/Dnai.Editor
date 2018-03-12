#ifndef DNAI_MODELS_DECLARABLE_LISTTYPE_H
#define DNAI_MODELS_DECLARABLE_LISTTYPE_H

#include "dnai/models/gui/data/listtype.h"
#include "entity.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			namespace declarable
			{
				class ListType : public interfaces::IEntity, public interfaces::IModelData<data::ListType>, public interfaces::ASerializable<ListType>
				{
				public:
					explicit ListType();
					//Implementation of ISerializable
					void serialize(QJsonObject& obj) const override;
				protected:
					void _deserialize(const QJsonObject& obj) override;
					//Implementation of IModelData
				public:
					const data::ListType& data() const override;
					bool setData(const data::ListType& data) override;
				public:
					int index() const override;
					bool setIndex(int index) override;
					int listIndex() const override;
					bool setListIndex(int listIndex) override;
					const QString& description() const override;
					bool setDescription(const QString& description) override;

				protected:
					data::ListType m_data;
				};
			}
		}
	}
}

#endif //DNAI_MODELS_DECLARABLE_LISTTYPE_H