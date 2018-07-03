#include "dnai/models/gui/declarable/function.h"

#include <QJsonArray>
#include <QDebug>
#include "dnai/models/entity.h"
#include "dnai/models/gui/instruction.h"
#include "dnai/models/gui/entitylist.h"

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
					m_finputs = new EntityList(&m_data.inputs);
					m_foutputs = new EntityList(&m_data.outputs);
				}

				void Function::serialize(QJsonObject& obj) const
				{	
					Entity::serialize(obj);
                    obj["inputs"] = serializeList<models::Entity>(m_data.inputs);
                    obj["outputs"] = serializeList<models::Entity>(m_data.outputs);
                    obj["instructions"] = serializeList<models::gui::Instruction>(m_data.instructions);
					obj["iolinks"] = serializeList<models::gui::IoLink>(m_data.iolinks);
					obj["flowlinks"] = serializeList<models::gui::FlowLink>(m_data.flowlinks);

                    QJsonObject ep;

                    ep["x"] = m_entryPoint.x;
                    ep["y"] = m_entryPoint.y;
                    ep["guid"] = m_entryPoint.guid.toString();

                    obj["entryPoint"] = ep;
				}

				void Function::_deserialize(const QJsonObject& obj)
				{
					Entity::_deserialize(obj);

					foreach(auto input, obj["inputs"].toArray()) {
						const auto core = new gcore::Entity(::core::ENTITY::VARIABLE);
						auto ent = models::Entity::deserialize(input.toObject(), core);
                        m_data.inputs.append(ent);
					}
					foreach(auto output, obj["outputs"].toArray()) {
						const auto core = new gcore::Entity(::core::ENTITY::VARIABLE);
						auto ent = models::Entity::deserialize(output.toObject(), core);
						m_data.outputs.append(ent);
					}
					foreach(auto node, obj["instructions"].toArray()) {
						addInstruction(Instruction::deserialize(node.toObject()));
					}
					foreach(auto link, obj["iolinks"].toArray()) {
						appendIoLink(models::gui::IoLink::deserialize(link.toObject()));
					}
					foreach(auto link, obj["flowlinks"].toArray()) {
						appendFlowLink(models::gui::FlowLink::deserialize(link.toObject()));
                    }

                    if (obj.contains("entryPoint"))
                    {
                        setEntryPointX(obj["entryPoint"]["x"].toInt());
                        setEntryPointY(obj["entryPoint"]["y"].toInt());
                        setEntryPoint(obj["entryPoint"]["guid"].toString());
                    }
				}

				const QList<models::Entity*>& Function::inputs() const
				{
					return m_data.inputs;
				}

				bool Function::setInputs(const QList<models::Entity*>& inputs)
				{
					if (m_data.inputs == inputs)
						return false;
					m_data.inputs = inputs;
					return true;
				}

				const QList<models::Entity*> &Function::outputs() const
				{
					return m_data.outputs;
				}

				bool Function::setOutputs(const QList<models::Entity*>& outputs)
				{
					if (m_data.outputs == outputs)
						return false;
					m_data.outputs = outputs;
					return true;
				}

				const QList<models::gui::Instruction*>& Function::instructions() const
				{
					return m_data.instructions;
				}

                void Function::addInput(models::Entity *var)
				{
					for (auto i : m_data.inputs)
					{
                        if (i->name() == var->name())
							return;
					}
                    m_finputs->append(var);
					emit inputModelsChanged(m_finputs);
				}

                void Function::addOutput(models::Entity *var)
				{
                    qDebug() << "================Add output";
					for (auto i : m_data.outputs)
					{
                        if (i->name() == var->name())
							return;
					}
                    m_foutputs->append(var);
					emit outputModelsChanged(m_foutputs);
				}

				void Function::removeInput(const QString& name)
				{
					m_finputs->remove(name);
					emit inputModelsChanged(m_finputs);
				}

				void Function::removeOutput(const QString& name)
				{
					m_foutputs->remove(name);
					emit outputModelsChanged(m_foutputs);
				}

				void Function::moveInputUp(const int index)
				{
					m_finputs->moveUp(index);
					emit inputModelsChanged(m_finputs);
				}

				void Function::moveOutputUp(const int index)
				{
					m_foutputs->moveUp(index);
					emit outputModelsChanged(m_foutputs);
				}

				void Function::moveInputDown(const int index)
				{
					m_finputs->moveDown(index);
					emit inputModelsChanged(m_finputs);
				}

				void Function::moveOutputDown(const int index)
				{
					m_foutputs->moveDown(index);
					emit outputModelsChanged(m_foutputs);
                }

				EntityList *Function::inputModels() const
				{
					return m_finputs;
				}

				EntityList *Function::outputModels() const
				{
					return m_foutputs;
				}

				void Function::setInputModels(EntityList* inputs)
				{
					if (inputs == m_finputs)
						return;
					m_finputs = inputs;
					emit inputModelsChanged(inputs);
				}

				void Function::setOutputModels(EntityList* outputs)
				{
					if (outputs == m_foutputs)
						return;
					m_foutputs = outputs;
					emit outputModelsChanged(outputs);
				}

				void Function::addInstruction(Instruction* instruction)
				{
					m_functionsHash[instruction->guiUuid()] = instruction;
                    m_data.instructions.append(instruction);
                }

                void Function::removeInstruction(Instruction *instruction)
                {
                    m_functionsHash.remove(instruction->guiUuid());
                    m_data.instructions.removeOne(instruction);
                }

				Instruction *Function::getInstruction(const QUuid &uuid)
				{
					return m_functionsHash[uuid];
				}

                quint32 Function::getInputId(const QString &name) const
                {
                    for (models::Entity *curr : inputs())
                    {
                        if (curr->name() == name)
                            return curr->id();
                    }
                    return core::UNDEFINED_ID;
                }

                quint32 Function::getOutputId(const QString &name) const
                {
                    for (models::Entity *curr : outputs())
                    {
                        if (curr->name() == name)
                            return curr->id();
                    }
                    return core::UNDEFINED_ID;
                }

                Instruction *Function::getInstruction(quint32 uid) const
                {
                    for (models::gui::Instruction *curr : data().instructions)
                    {
                        if (curr->Uid() == uid)
                            return curr;
                    }
                    return nullptr;
                }

                Instruction *Function::getInstruction(const QUuid &guid) const
                {
                    for (models::gui::Instruction *curr : m_data.instructions)
                    {
                        if (curr->guiUuid() == guid)
                            return curr;
                    }
                    return nullptr;
                }

                bool Function::hasInput(const QString &name, QUuid const &type) const
                {
                    for (models::Entity *curr : m_data.inputs)
                    {
                        if (curr->name() == name)
                        {
                            if (!type.isNull())
                            {
                                return curr->guiModel<models::Variable>()->varType() == type;
                            }
                            return true;
                        }
                    }
                    return false;
                }

                Instruction *Function::entryPoint() const
                {
                    if (m_entryPoint.guid.isNull())
                        return nullptr;
                    return getInstruction(m_entryPoint.guid);
                }

                void Function::setEntryPoint(QUuid uid)
                {
                    m_entryPoint.guid = uid;
                }

                qint32 Function::entryPointX() const
                {
                    return m_entryPoint.x;
                }

                void Function::setEntryPointX(qint32 x)
                {
                    m_entryPoint.x = x;
                }

                qint32 Function::entryPointY() const
                {
                    return m_entryPoint.y;
                }

                void Function::setEntryPointY(qint32 y)
                {
                    m_entryPoint.y = y;
                }

				const QList<dnai::models::gui::IoLink*> &Function::iolinks() const
				{
					return m_data.iolinks;
				}

				bool Function::setIoLinks(const QList<dnai::models::gui::IoLink*>& value)
				{
					if (value == m_data.iolinks)
						return false;
					m_data.iolinks = value;
					return true;
				}

				void Function::appendIoLink(dnai::models::gui::IoLink* link)
				{
					if (!m_data.iolinks.contains(link))
                    {
						m_data.iolinks.append(link);
					}
				}

				void Function::removeIoLink(dnai::models::gui::IoLink* link)
				{
					if (m_data.iolinks.contains(link))
                        m_data.iolinks.removeOne(link);
                }

                IoLink *Function::findIOLink(const QUuid &instruction, const QString &input) const
                {
                    for (IoLink *curr : m_data.iolinks)
                    {
                        if (curr->data().inputUuid == instruction && curr->data().inputName == input)
                        {
                            return curr;
                        }
                    }
                    return nullptr;
                }

				const QList<dnai::models::gui::FlowLink*>& Function::flowlinks() const
				{
					return m_data.flowlinks;
				}

				bool Function::setFlowLinks(const QList<dnai::models::gui::FlowLink*>& fl)
				{
					if (m_data.flowlinks == fl)
						return false;
					m_data.flowlinks = fl;
					return true;
				}

				void Function::appendFlowLink(dnai::models::gui::FlowLink* fl)
				{
					if (!m_data.flowlinks.contains(fl))
						m_data.flowlinks.append(fl);
				}

				void Function::removeFlowLink(dnai::models::gui::FlowLink* link)
				{
					if (m_data.flowlinks.contains(link))
                        m_data.flowlinks.removeOne(link);
                }

                FlowLink *Function::findFlowLink(const QUuid &from, quint32 outPin, const QUuid &to) const
                {
                    for (FlowLink *curr : m_data.flowlinks)
                    {
                        if (curr->data().from == from && curr->data().outIndex == outPin)
                        {
                            if (to.isNull() || curr->data().to == to)
                                return curr;
                        }
                    }
                    return nullptr;
                }
			}
		}
	}
}
