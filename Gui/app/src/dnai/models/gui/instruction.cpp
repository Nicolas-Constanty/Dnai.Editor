#include <QJsonObject>
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
				const auto getRandomString = [](int size)
				{
					const QString possibleCharacters(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~");

					QString randomString;
					for (auto i = 0; i< size; ++i)
					{
						auto index = qrand() % possibleCharacters.length();
						auto nextChar = possibleCharacters.at(index);
						randomString.append(nextChar);
					}
					return randomString;
				};
				m_data.guiUuid = QUuid::createUuidV5(QUuid::createUuid(), getRandomString(128));
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
				obj["x"] = m_data.x;
                obj["y"] = m_data.y;

                QJsonArray linkEntities;

                for (QString const &curr : m_data.linked) {
                    linkEntities.append(curr);
                }

                obj["linked"] = linkEntities;
				obj["guiUuid"] = m_data.guiUuid.toString();
                obj["nodeMenuPath"] = nodeMenuPath();
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
				m_data.x = obj["x"].toInt();
				m_data.y = obj["y"].toInt();
                foreach (auto link, obj["linked"].toArray()) {
                    m_data.linked.append(link.toString());
                }
				m_data.guiUuid = obj["guiUuid"].toString();
                m_data.nodeMenuPath = obj["nodeMenuPath"].toString();
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

            quint32 Instruction::Uid() const
            {
                return m_data.uid;
            }

            bool Instruction::setUid(quint32 id)
            {
                if (m_data.uid == id)
                    return false;
                m_data.uid = id;
                return true;
            }

            const QList<QString> &Instruction::linked() const
            {
                return m_data.linked;
            }

            bool Instruction::setLinkedEntities(const QList<QString> &value)
            {
                if (value == m_data.linked)
                    return false;
                m_data.linked = value;
                return true;
            }

			const QUuid& Instruction::guiUuid() const
			{
				return m_data.guiUuid;
			}

			bool Instruction::setGuiUuid(const QUuid& value)
			{
				if (value == m_data.guiUuid)
					return false;
				m_data.guiUuid = value;
                return true;
            }

            const QString &Instruction::nodeMenuPath() const
            {
                return m_data.nodeMenuPath;
            }

            bool Instruction::setNodeMenuPath(const QString &value)
            {
                if (nodeMenuPath() == value)
                    return false;
                m_data.nodeMenuPath = value;
                return true;
            }
		}
	}
}
