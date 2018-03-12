#include <QJsonArray>
#include "dnai/models/gui/declarable/context.h"
#include "dnai/models/gui/instruction.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			namespace declarable
			{
				Context::Context()
				{
				}

				void Context::serialize(QJsonObject& obj) const
				{
					obj["description"] = m_data.description;
					obj["index"] = m_data.index;
					obj["listIndex"] = m_data.listIndex;
					obj["contexts"] = serializeList<Context>(m_data.contexts);
					obj["classes"] = serializeList<ObjectType>(m_data.classes);
					obj["variables"] = serializeList<Variable>(m_data.variables);
					obj["enums"] = serializeList<EnumType>(m_data.enums);
					obj["listobjs"] = serializeList<ListType>(m_data.listobjs);
					obj["functions"] = serializeList<Function>(m_data.functions);
				}

				void Context::_deserialize(const QJsonObject& obj)
				{
					m_data.description = obj["description"].toString();
					m_data.index = obj["index"].toInt();
					m_data.listIndex = obj["listIndex"].toInt();
					foreach(auto context, obj["contexts"].toArray()) {
						m_data.contexts.append(deserialize(context.toObject()));
					}
					foreach(auto classe, obj["classes"].toArray()) {
						m_data.classes.append(ObjectType::deserialize(classe.toObject()));
					}
					foreach(auto variable, obj["variables"].toArray()) {
						m_data.variables.append(Variable::deserialize(variable.toObject()));
					}
					foreach(auto enumobj, obj["enums"].toArray()) {
						m_data.enums.append(EnumType::deserialize(enumobj.toObject()));
					}
					foreach(auto listobj, obj["listobjs"].toArray()) {
						m_data.listobjs.append(ListType::deserialize(listobj.toObject()));
					}
					foreach(auto function, obj["functions"].toArray()) {
						m_data.functions.append(Function::deserialize(function.toObject()));
					}
				}

				const data::Context& Context::data() const
				{
					return m_data;
				}

				bool Context::setData(const data::Context& data)
				{
					if (m_data == data)
						return false;
					m_data = data;
					return true;
				}

				int Context::index() const
				{
					return m_data.index;
				}

				bool Context::setIndex(int index)
				{
					if (m_data.index == index)
						return false;
					m_data.index = index;
					return true;
				}

				int Context::listIndex() const
				{
					return m_data.listIndex;
				}

				bool Context::setListIndex(int listIndex)
				{
					if (m_data.listIndex == listIndex)
						return false;
					m_data.listIndex = listIndex;
					return true;
				}

				const QString& Context::description() const
				{
					return m_data.description;
				}

				bool Context::setDescription(const QString& description)
				{
					if (m_data.description == description)
						return false;
					m_data.description = description;
					return true;
				}
			}
		}
	}
}
