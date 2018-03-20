#include "dnai/models/gui/declarable/function.h"

#include <QJsonArray>
#include "dnai/models/gui/instruction.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			namespace declarable
			{
				Function::Function(QObject* parent)
				{
				}

				void Function::serialize(QJsonObject& obj) const
				{	
					Entity::serialize(obj);
                    QJsonArray instructions;
                    foreach(const interfaces::IInstruction *instruction, m_data.instructions) {
                        QJsonObject var;
                        if (const auto func = dynamic_cast<const Function *>(instruction))
                            func->serialize(var);
                        else if (const auto inst = dynamic_cast<const Instruction *>(instruction))
                            inst->serialize(var);
                        instructions.append(var);
                    }
					obj["variables"] = serializeList<Variable>(m_data.variables);
					obj["inputs"] = serializeList<Input>(m_data.inputs);
					obj["outputs"] = serializeList<Output>(m_data.outputs);
					obj["instructions"] = instructions;
				}

				void Function::_deserialize(const QJsonObject& obj)
				{
					Entity::_deserialize(obj);
					foreach(auto variable, obj["variables"].toArray()) {
						m_data.variables.append(Variable::deserialize(variable.toObject()));
					}

					foreach(auto input, obj["inputs"].toArray()) {
						m_data.inputs.append(Input::deserialize(input.toObject()));
					}

					foreach(auto output, obj["outputs"].toArray()) {
						m_data.inputs.append(Input::deserialize(output.toObject()));
					}

					foreach(auto node, obj["instructions"].toArray()) {
						if (node.toObject()["instruction_id"].toString().isEmpty())
							m_data.instructions.append(deserialize(node.toObject()));
						else
							m_data.instructions.append(Instruction::deserialize(node.toObject()));
					}
				}

				QList<models::gui::Input*> Function::inputs() const
				{
					return m_data.inputs;
				}

				bool Function::setInputs(const QList<models::gui::Input*>& inputs)
				{
					if (m_data.inputs == inputs)
						return false;
					m_data.inputs = inputs;
					return true;
				}

				QList<gui::Output*> Function::outputs() const
				{
					return m_data.outputs;
				}

				bool Function::setOutputs(const QList<gui::Output*>& outputs)
				{
					if (m_data.outputs == outputs)
						return false;
					m_data.outputs = outputs;
					return true;
				}

				models::gui::Flow* Function::flowIn() const
				{
					return m_data.flowIn;
				}

				bool Function::setFlowIn(gui::Flow* flow)
				{
					if (m_data.flowIn == flow)
						return false;
					m_data.flowIn = flow;
					return true;
				}

				gui::Flow* Function::flowOut() const
				{
					return m_data.flowOut;
				}

				bool Function::setFlowOut(gui::Flow* flow)
				{
					if (m_data.flowOut == flow)
						return false;
					m_data.flowOut = flow;
					return true;
				}
			}
		}
	}
}
