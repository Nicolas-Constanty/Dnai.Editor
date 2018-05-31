#include "dnai/models/gui/declarable/function.h"

#include <QJsonArray>
#include <QDebug>
#include "dnai/models/entity.h"
#include "dnai/models/gui/instruction.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			namespace declarable
			{
				FunctionInputs::FunctionInputs(QList<models::Entity*>*l) : QAbstractListModel(nullptr)
				{
					m_list = l;
				}

				int FunctionInputs::rowCount(const QModelIndex& parent) const
				{
					return m_list->count();
				}

				QVariant FunctionInputs::data(const QModelIndex& index, const int role) const
				{
					if (!index.isValid())
						return QVariant();
					if (role == Name)
						return QVariant::fromValue(m_list->at(index.row())->name());
					else if (role == Type)
						return QVariant::fromValue(dynamic_cast<gui::declarable::Variable*>(m_list->at(index.row())->guiModel())->varType());
					return QVariant();
				}

                void FunctionInputs::add(models::Entity *var)
				{
					beginInsertRows(QModelIndex(), m_list->length(), m_list->length());
                    /*auto input = new gui::declarable::Variable();
                    auto entity = new models::Entity(new gcore::Entity(::core::ENTITY::VARIABLE));
                    entity->setGuiModel(input);
                    input->setVarType(varType);
                    if (name.isEmpty())
                        entity->setName(QString("Empty : ") + QString::number(m_list->count()));
					else
                        entity->setName(name);*/
                    m_list->append(var);
					endInsertRows();
				}

				void FunctionInputs::moveUp(const int index)
				{
					if (index < 0 || m_list->length() <= 1)
						return;
					const auto start = index % m_list->length();
					const auto end = (start <= 0) ? m_list->length() - 1 : start - 1;
					beginMoveRows(QModelIndex(), start, start, QModelIndex(), start == 0 ? m_list->length() : end );
					m_list->swap(start, end);
					endMoveRows();
				}

				void FunctionInputs::moveDown(const int index)
				{
					if (index < 0 || m_list->length() <= 1)
						return;
					const auto start = index % m_list->length();
					const auto end = (start + 1) % m_list->length();
					beginMoveRows(QModelIndex(), start, start, QModelIndex(), end == 0 ? 0 : end + 1);
					m_list->swap(start, end);
					endMoveRows();
				}

				void FunctionInputs::remove(const QString& name)
				{
					auto index = 0;
					for (auto i : *m_list)
					{
						if (i->name() == name)
							break;
						index++;
					}
					beginRemoveRows(QModelIndex(), index, index);
					m_list->removeAt(index);
					endRemoveRows();
				}

				bool FunctionInputs::setData(const QModelIndex& index, const QVariant& value, int role)
				{
					auto result = false;
					if (role == Name)
					{
						m_list->at(index.row())->setName(value.toString());
						result = true;
					}
					else if (role == Type)
						result = dynamic_cast<models::gui::declarable::Variable*>(m_list->at(index.row())->guiModel())->setVarType(value.toInt());
					if (result)
						emit dataChanged(index, index);

					return result;
				}

				bool FunctionInputs::setData(const int index, const QVariant& value, int role)
				{
					return setData(createIndex(index, 0), value, role);
				}

				QHash<int, QByteArray> FunctionInputs::roleNames() const {
					QHash<int, QByteArray> roles;
					roles[Name] = "name";
					roles[Type] = "varType";
					return roles;
				}

				FunctionOutputs::FunctionOutputs(QList<models::Entity*> *l) : QAbstractListModel(nullptr)
				{
					m_list = l;
				}

				int FunctionOutputs::rowCount(const QModelIndex& parent) const
				{
					return m_list->count();
				}

				QVariant FunctionOutputs::data(const QModelIndex& index, const int role) const
				{
					if (!index.isValid())
						return QVariant();
					if (role == Name)
						return QVariant::fromValue(m_list->at(index.row())->name());
					else if (role == Type)
						return QVariant::fromValue(dynamic_cast<gui::declarable::Variable*>(m_list->at(index.row())->guiModel())->varType());
					return QVariant();
				}

                void FunctionOutputs::add(models::Entity *var)
				{
					beginInsertRows(QModelIndex(), m_list->length(), m_list->length());
                    /*auto output = new gui::declarable::Variable();
					auto entity = new models::Entity(new gcore::Entity(::core::ENTITY::VARIABLE));
					entity->setGuiModel(output);
					output->setVarType(varType);
					if (name.isEmpty())
                        entity->setName(QString("Empty : ") + QString::number(m_list->count()));
					else
                        entity->setName(name);*/
                    m_list->append(var);
					endInsertRows();
				}

				void FunctionOutputs::moveUp(const int index)
				{
					if (index < 0 || m_list->length() <= 1)
						return;
					const auto start = index % m_list->length();
					const auto end = (start <= 0) ? m_list->length() - 1 : start - 1;
					beginMoveRows(QModelIndex(), start, start, QModelIndex(), start == 0 ? m_list->length() : end);
					m_list->swap(start, end);
					endMoveRows();
				}

				void FunctionOutputs::moveDown(const int index)
				{
					if (index < 0 || m_list->length() <= 1)
						return;
					const auto start = index % m_list->length();
					const auto end = (start + 1) % m_list->length();
					beginMoveRows(QModelIndex(), start, start, QModelIndex(), end == 0 ? 0 : end + 1);
					m_list->swap(start, end);
					endMoveRows();
				}

				void FunctionOutputs::remove(const QString& name)
				{
					auto index = 0;
					for (auto i : *m_list)
					{
						if (i->name() == name)
							break;
						index++;
					}
					beginRemoveRows(QModelIndex(), index, index);
					m_list->removeAt(index);
					endRemoveRows();
				}

				bool FunctionOutputs::setData(const QModelIndex& index, const QVariant& value, int role)
				{
					auto result = false;
					if (role == Name)
					{
						m_list->at(index.row())->setName(value.toString());
						result = true;
					}
					else if (role == Type)
						result = dynamic_cast<models::gui::declarable::Variable*>(m_list->at(index.row())->guiModel())->setVarType(value.toInt());
					if (result)
						emit dataChanged(index, index);

					return result;
				}

				bool FunctionOutputs::setData(const int index, const QVariant& value, int role)
				{
					return setData(createIndex(index, 0), value, role);
				}

				QHash<int, QByteArray> FunctionOutputs::roleNames() const
				{
					QHash<int, QByteArray> roles;
					roles[Name] = "name";
					roles[Type] = "varType";
					return roles;
				}

				Function::Function(QObject* parent) : QObject(parent)
				{
					m_finputs = new FunctionInputs(&m_data.inputs);
					m_foutputs = new FunctionOutputs(&m_data.outputs);
				}

				void Function::serialize(QJsonObject& obj) const
				{	
					Entity::serialize(obj);
                    QJsonArray instructions;
                    foreach(const auto instruction, m_data.instructions) {
                        QJsonObject var;
                        instruction->serialize(var);
                        instructions.append(var);
                    }
                    obj["inputs"] = serializeList<models::Entity>(m_data.inputs);
                    obj["outputs"] = serializeList<models::Entity>(m_data.outputs);
                    obj["instructions"] = instructions;
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
                    m_finputs->add(var);
					emit inputModelsChanged(m_finputs);
				}

                void Function::addOutput(models::Entity *var)
				{
					for (auto i : m_data.outputs)
					{
                        if (i->name() == var->name())
							return;
					}
                    m_foutputs->add(var);
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

                /*void Function::updateInputName(const int index, const QString& name)
				{
					m_finputs->setData(index, name, FunctionInputs::Name);
					emit inputModelsChanged(m_finputs);
				}

				void Function::updateInputVarType(const int index, const qint32 varType)
				{
					m_finputs->setData(index, varType, FunctionInputs::Type);
					emit inputModelsChanged(m_finputs);
				}

				void Function::updateOutputName(const int index, const QString& name)
				{
					m_foutputs->setData(index, name, FunctionInputs::Name);
					emit outputModelsChanged(m_foutputs);
				}

				void Function::updateOutputVarType(const int index, const qint32 varType)
				{
					m_foutputs->setData(index, varType, FunctionInputs::Type);
					emit outputModelsChanged(m_foutputs);
                }*/

				FunctionInputs *Function::inputModels() const
				{
					return m_finputs;
				}

				FunctionOutputs *Function::outputModels() const
				{
					return m_foutputs;
				}

				void Function::setInputModels(FunctionInputs* inputs)
				{
					if (inputs == m_finputs)
						return;
					m_finputs = inputs;
					emit inputModelsChanged(inputs);
				}

				void Function::setOutputModels(FunctionOutputs* outputs)
				{
					if (outputs == m_foutputs)
						return;
					m_foutputs = outputs;
					emit outputModelsChanged(outputs);
				}

				void Function::addInstruction(Instruction* instruction)
				{
					m_data.instructions.append(instruction);
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
			}
		}
	}
}
