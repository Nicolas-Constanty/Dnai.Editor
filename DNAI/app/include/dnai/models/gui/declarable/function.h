#ifndef DNAI_MODELS_GUI_DECLARABLE_FUNCTION_H
#define DNAI_MODELS_GUI_DECLARABLE_FUNCTION_H

#include "dnai/interfaces/ientity.h"
#include "dnai/interfaces/iinstruction.h"
#include "dnai/models/gui/data/function.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			namespace declarable
			{
				class Function : public interfaces::IInstruction, public Entity<data::Function, Function>
                {
				public:
                    explicit Function(QObject *parent = nullptr);
                    //Implementation of ISerializable
					void serialize(QJsonObject& obj) const override;
				protected:
					void _deserialize(const QJsonObject& obj) override;

				public:
					//Implementation of IInstruction
					QList<models::gui::Input*> inputs() const override;
					bool setInputs(const QList<models::gui::Input*>& inputs) override;
					QList<models::gui::Output*> outputs() const override;
					bool setOutputs(const QList<models::gui::Output*>& outputs) override;
					models::gui::Flow* flowIn() const override;
					bool setFlowIn(models::gui::Flow* flow) override;
					models::gui::Flow* flowOut() const override;
					bool setFlowOut(models::gui::Flow* flow) override;
				};
			}
		}
	}
}

#endif //DNAI_MODELS_GUI_DECLARABLE_FUNCTION_H
