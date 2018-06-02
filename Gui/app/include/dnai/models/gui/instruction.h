#ifndef DNAI_MODELS_GUI_INSTRUCTION_H
#define DNAI_MODELS_GUI_INSTRUCTION_H

#include "dnai/interfaces/imodeldata.h"
#include "dnai/interfaces/iserializable.h"
#include "dnai/models/gui/data/instruction.h"
#include "dnai/interfaces/iinstruction.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			class Instruction : public QObject, public interfaces::IModelData<data::Instruction>, public interfaces::ASerializable<Instruction>
            {
				Q_OBJECT
			public:
                explicit Instruction(QObject *parent = nullptr);
                //Implementation of ISerializable
                virtual void serialize(QJsonObject& obj) const override;
			protected:
                virtual void _deserialize(const QJsonObject& obj) override;
				//Implementation of IModelData
			public:
				const data::Instruction& data() const override;
				bool setData(const data::Instruction& data) override;
				//Implementation of IInstruction
                const QList<models::gui::Input*> &inputs() const;
                bool setInputs(const QList<models::gui::Input*>& inputs);

				const QList<models::gui::Output*> &outputs() const;
                bool setOutputs(const QList<models::gui::Output*>& outputs);

				models::gui::Flow* flowIn() const;
                bool setFlowIn(models::gui::Flow* flow);

				const QList<models::gui::Flow*> &flowOut() const;
                bool setFlowOut(const QList<models::gui::Flow*> &flow);

				qint32 x() const;
				bool setX(qint32 x);

				qint32 y() const;
				bool setY(qint32 y);

				qint32 instruction_id() const;
				bool setInstructionId(qint32 id);

                quint32 Uid() const;
                bool setUid(quint32 id);

                QList<QString> const &linked() const;
                bool setLinkedEntities(QList<QString> const &value);

			private:
				data::Instruction m_data;
			};
		}
	}
}

#endif //DNAI_MODELS_GUI_INSTRUCTION_H
