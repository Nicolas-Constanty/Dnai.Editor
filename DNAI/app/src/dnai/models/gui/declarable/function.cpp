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
					QJsonArray variables;
					foreach(const Variable *variable, m_data.variables) {
						QJsonObject var;
						variable->serialize(var);
						variables.append(var);
					}

					QJsonArray inputs;
					foreach(const Input *input, m_data.inputs) {
						QJsonObject var;
						input->serialize(var);
						inputs.append(var);
					}

					QJsonArray outputs;
					foreach(const Output *output, m_data.outputs) {
						QJsonObject var;
						output->serialize(var);
						outputs.append(var);
					}

					QJsonArray instructions;
					foreach(const interfaces::IInstruction *instruction, m_data.instructions) {
						QJsonObject var;
						if (const auto func = dynamic_cast<const Function *>(instruction))
							func->serialize(var);
						else if (const auto inst = dynamic_cast<const Instruction *>(instruction))
							inst->serialize(var);
						instructions.append(var);
					}

					obj["variables"] = variables;
					obj["inputs"] = inputs;
					obj["outputs"] = outputs;
					obj["instructions"] = instructions;
				}

				void Function::_deserialize(const QJsonObject& obj)
				{

					foreach(auto variable, obj["variables"].toArray()) {
						m_data.variables.append(Variable::deserialize(variable.toObject()));
					}

					foreach(auto input, obj["inputs"].toArray()) {
						m_data.inputs.append(Input::deserialize(input.toObject()));
					}

					foreach(auto output, obj["outputs"].toArray()) {
						m_data.inputs.append(Input::deserialize(output.toObject()));
					}

					foreach(auto node, obj["nodes"].toArray()) {
						if (node.toObject()["instruction_id"].toString().isEmpty())
							m_data.instructions.append(deserialize(node.toObject()));
						else
							m_data.instructions.append(Instruction::deserialize(node.toObject()));
					}
				}

				const data::Function& Function::data() const
				{
					return m_data;
				}

				bool Function::setData(const data::Function& data)
				{
                    if (m_data == data)
                        return false;
					m_data = data;
                    return true;
				}

				int Function::index() const
				{
					return m_data.index;
				}

				bool Function::setIndex(int index)
				{
					if (index == m_data.index)
						return false;
					m_data.index = index;
					return true;
				}

				int Function::listIndex() const
				{
					return m_data.listIndex;
				}

				bool Function::setListIndex(int listIndex)
				{
					if (listIndex == m_data.listIndex)
						return false;
					m_data.listIndex = listIndex;
					return true;
				}

				const QString& Function::description() const
				{
					return m_data.description;
				}

				bool Function::setDescription(const QString& description)
				{
					if (description == m_data.description)
						return false;
					m_data.description = description;
					return true;
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
