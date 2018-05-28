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
				Function::Function(QObject* parent) : QObject(parent)
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
                    obj["inputs"] = serializeList<Input>(m_data.inputs);
                    obj["outputs"] = serializeList<Output>(m_data.outputs);
                    obj["instructions"] = instructions;
				}

				void Function::_deserialize(const QJsonObject& obj)
				{
					Entity::_deserialize(obj);

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

				void Function::addInput(const QString& name, qint32 varType)
				{
					for (auto i : m_data.inputs)
					{
						if (i->data().name == name)
							return;
					}
					auto input = new gui::Input();
					input->setVarType(varType);
					input->setName(name);
					m_data.inputs.append(input);
					emit inputsChanged(m_data.inputs);
				}

				void Function::addOutput(const QString& name, qint32 varType)
				{
					for (auto i : m_data.outputs)
					{
						if (i->data().name == name)
							return;
					}
					auto output = new gui::Output();
					output->setVarType(varType);
					output->setName(name);
					m_data.outputs.append(output);
					emit outputsChanged(m_data.outputs);
				}

				void Function::removeInput(const QString& name)
				{
					int index = 0;
					for (auto i : m_data.inputs)
					{
						if (i->data().name == name)
							break;
						index++;
					}
					m_data.inputs.removeAt(index);
					emit inputsChanged(m_data.inputs);
				}

				void Function::removeOutput(const QString& name)
				{
					int index = 0;
					for (auto i : m_data.outputs)
					{
						if (i->data().name == name)
							break;
						index++;
					}
					m_data.outputs.removeAt(index);
					emit outputsChanged(m_data.outputs);
				}

				void Function::moveInputUp(int index)
				{
					if (index < 0)
						return;
					const auto start = index % m_data.inputs.length();
					const auto end = (start <= 0) ? m_data.inputs.length() - 1 : start - 1;
					m_data.inputs.swap(start, end);
					emit inputsChanged(m_data.inputs);
				}

				void Function::moveOutputUp(int index)
				{
					if (index < 0)
						return;
					const auto start = index % m_data.outputs.length();
					const auto end = (start <= 0) ? m_data.outputs.length() - 1 : start - 1;
					m_data.outputs.swap(start, end);
					emit outputsChanged(m_data.outputs);
				}

				void Function::moveInputDown(int index)
				{
					if (index < 0)
						return;
					const auto start = index % m_data.inputs.length();
					const auto end = (start + 1) % m_data.inputs.length();
					m_data.inputs.swap(start, end);
					emit inputsChanged(m_data.inputs);
				}

				void Function::moveOutputDown(int index)
				{
					if (index < 0)
						return;
					const auto start = index % m_data.outputs.length();
					const auto end = (start + 1) % m_data.outputs.length();
					m_data.outputs.swap(start, end);
					emit outputsChanged(m_data.outputs);
				}
			}
		}
	}
}
