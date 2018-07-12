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

                Q_PROPERTY(qint32 uid READ Uid WRITE setUid)
                Q_PROPERTY(QList<QString> linked READ linked WRITE setLinkedEntities)

			public:
                explicit Instruction(QObject *parent = nullptr);
                //Implementation of ISerializable
                void serialize(QJsonObject& obj) const override;
			protected:
                void _deserialize(const QJsonObject& obj) override;
				//Implementation of IModelData
			public:
				const data::Instruction& data() const override;
				bool setData(const data::Instruction& data) override;

				//Implementation of IInstruction
                Q_INVOKABLE const QList<models::gui::Input*> &inputs() const;
                bool setInputs(const QList<models::gui::Input*>& inputs);
                Q_INVOKABLE models::gui::Input *getInput(QString const &name) const;
                bool hasInput(QString const &name) const;
                Q_INVOKABLE QString getInputValue(QString const &name) const;
                Q_INVOKABLE QString getInputType(QString const &name) const;

                const QList<models::gui::Output*> &outputs() const;
                bool hasOutput(QString const &name) const;
                bool setOutputs(const QList<models::gui::Output*>& outputs);
                Q_INVOKABLE models::gui::Output *getOutput(QString const &name) const;
                Q_INVOKABLE QString getOutputType(QString const &name) const;

				models::gui::Flow* flowIn() const;
                bool setFlowIn(models::gui::Flow* flow);

				const QList<models::gui::Flow*> &flowOut() const;
                bool setFlowOut(const QList<models::gui::Flow*> &flow);

				qint32 instruction_id() const;
				bool setInstructionId(qint32 id);

                quint32 Uid() const;
                bool setUid(quint32 id);

                QList<QString> const &linked() const;
                bool setLinkedEntities(QList<QString> const &value);

				const QUuid &guiUuid() const;
				bool setGuiUuid(const QUuid &value);

                const QString &nodeMenuPath() const;
                bool setNodeMenuPath(QString const &value);

				qint32 x() const;
				Q_INVOKABLE bool setX(qint32 x);
				
				qint32 y() const;
				Q_INVOKABLE bool setY(qint32 y);

            private:
				data::Instruction m_data;
			};
		}
	}
}

#endif //DNAI_MODELS_GUI_INSTRUCTION_H
