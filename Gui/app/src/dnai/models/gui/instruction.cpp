#include <QJsonObject>
#include <QJsonArray>
#include "dnai/models/gui/instruction.h"
#include "dnai/models/gui/declarable/variable.h"
#include "dnai/models/entity.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			Instruction::Instruction(QObject* parent) : QObject(parent)
			{
			}

			void Instruction::serialize(QJsonObject& obj) const
			{
				QJsonArray inputs;
				foreach(const auto input, m_data.inputs) {
					QJsonObject var;
					input->serialize(var);
					inputs.append(var);
				}

				QJsonArray outputs;
				foreach(const auto output, m_data.outputs) {
					QJsonObject var;
					output->serialize(var);
					outputs.append(var);
				}

				obj["inputs"] = inputs;
				obj["outputs"] = outputs;
				QJsonObject temp;
                if (m_data.flowIn != nullptr)
                {
                    m_data.flowIn->serialize(temp);
                    obj["flow_in"] = temp;
                }
				obj["flow_out"] = serializeList<Flow>(m_data.flowOut);
				obj["instruction_id"] = m_data.instructionId;
			}

			void Instruction::_deserialize(const QJsonObject& obj)
			{
				foreach(auto input, obj["inputs"].toArray()) {
					auto ent = gui::Input::deserialize(input.toObject());
					m_data.inputs.append(ent);
		        }
				foreach(auto output, obj["m_outputs"].toArray()) {
					auto ent = gui::Output::deserialize(output.toObject());
					m_data.outputs.append(ent);
				}
				m_data.flowIn = Flow::deserialize(obj["flow_in"].toObject());
				for (auto elem : obj["flow_out"].toArray())
					m_data.flowOut.append(Flow::deserialize(elem.toObject()));
				m_data.instructionId = obj["instruction_id"].toInt();
			}

			const data::Instruction& Instruction::data() const
			{
				return m_data;
			}

			bool Instruction::setData(const data::Instruction& data)
			{
                if (m_data == data)
                    return false;
				m_data = data;
                return true;
			}

            const QList<models::gui::Input*> &Instruction::inputs() const
			{
				return m_data.inputs;
			}

			bool Instruction::setInputs(const QList<models::gui::Input*>& inputs)
			{
				if (m_data.inputs == inputs)
					return false;
				m_data.inputs = inputs;
				return true;
			}

            const QList<models::gui::Output*> &Instruction::outputs() const
			{
				return m_data.outputs;
			}

            bool Instruction::setOutputs(const QList<models::gui::Output*>& outputs)
			{
				if (m_data.outputs == outputs)
					return false;
				m_data.outputs = outputs;
				return true;
			}

			models::gui::Flow* Instruction::flowIn() const
			{
				return m_data.flowIn;
			}

			bool Instruction::setFlowIn(models::gui::Flow* flow)
			{
				if (m_data.flowIn == flow)
					return false;
				m_data.flowIn = flow;
				return true;
			}

			const QList<models::gui::Flow*> &Instruction::flowOut() const
			{
				return m_data.flowOut;
			}

			bool Instruction::setFlowOut(const QList<models::gui::Flow*> &flow)
			{
				if (m_data.flowOut == flow)
					return false;
				m_data.flowOut = flow;
				return true;
			}

			qint32 Instruction::x() const
			{
				return m_data.x;
			}

			bool Instruction::setX(qint32 x)
			{
				if (m_data.x == x)
					return false;
				m_data.x = x;
				return true;
			}

			qint32 Instruction::y() const
			{
				return m_data.y;
			}

			bool Instruction::setY(qint32 y)
			{
				if (m_data.y == y)
					return false;
				m_data.y = y;
				return true;
			}

			qint32 Instruction::instruction_id() const
			{
				return m_data.instructionId;
			}

			bool Instruction::setInstructionId(qint32 id)
			{
				if (m_data.instructionId == id)
					return false;
				m_data.instructionId = id;
				return true;
			}
		}
	}
}
