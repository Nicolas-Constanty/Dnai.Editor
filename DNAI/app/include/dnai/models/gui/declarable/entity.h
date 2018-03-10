#ifndef DNAI_MODELS_GUI_DECLARABLE_ENTITY_H
#define DNAI_MODELS_GUI_DECLARABLE_ENTITY_H

#include "dnai/interfaces/imodeldata.h"
#include "dnai/interfaces/iserializable.h"
#include "dnai/models/gui/data/entity.h"
#include "dnai/interfaces/ientity.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			namespace declarable
			{
				
				class Entity : public interfaces::IEntity, public interfaces::IModelData<data::Entity>, public interfaces::ASerializable<Entity>
				{
					//IModelData implementation
				public:
					Entity();
					const data::Entity &data() const override;
					bool setData(const data::Entity& data) override;

					virtual int index() const override;
					virtual bool setIndex(int index) override;

					virtual int listIndex() const override;
					virtual bool setListIndex(int listIndex) override;

					virtual const QString &description() const override;
					virtual bool setDescription(const QString& description) override;

					~Entity() override;
					virtual void serialize(QJsonObject& obj) const override;
				protected:
					virtual void _deserialize(const QJsonObject& obj) override;
				private:
					data::Entity m_data;
				};
			}
		}
	}
}

#endif //DNAI_MODELS_GUI_DECLARABLE_ENTITY_H