#ifndef DNAI_MODELS_DECLARABLE_VARIABLE_H
#define DNAI_MODELS_DECLARABLE_VARIABLE_H

#include <QObject>
#include "dnai/models/gui/data/variable.h"
#include "entity.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			namespace declarable
			{
                class Variable : public interfaces::IEntity, public interfaces::IModelData<data::Variable>, public interfaces::ASerializable<Variable>
                {
				public:
                    explicit Variable(QObject *parent = nullptr);
                    //Implementation of ISerializable
					void serialize(QJsonObject& obj) const override;
				protected:
					void _deserialize(const QJsonObject& obj) override;
					//Implementation of IModelData
				public:
					const data::Variable& data() const override;
					bool setData(const data::Variable& data) override;
				public:
					int index() const override;
					bool setIndex(int index) override;
					int listIndex() const override;
					bool setListIndex(int listIndex) override;
					const QString& description() const override;
					bool setDescription(const QString& description) override;

				protected:
					data::Variable m_data;
				};
			}
		}
	}
}

#endif //DNAI_MODELS_DECLARABLE_VARIABLE_H
