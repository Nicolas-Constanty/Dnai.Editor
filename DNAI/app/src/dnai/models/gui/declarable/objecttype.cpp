#include "dnai/models/gui/declarable/objecttype.h"
#include "dnai/exceptions/notimplemented.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			namespace declarable
			{
				ObjectType::ObjectType()
				{
				}

				void ObjectType::serialize(QJsonObject& obj) const
				{
					obj["description"] = m_data.description;
					obj["index"] = m_data.index;
					obj["listIndex"] = m_data.listIndex;
					obj["classes"] = serializeList<ObjectType>(m_data.classes);
					obj["variables"] = serializeList<Variable>(m_data.variables);
					obj["attributes"] = serializeList<Variable>(m_data.attributes);
					obj["enums"] = serializeList<EnumType>(m_data.enums);
					obj["listobjs"] = serializeList<ListType>(m_data.listobjs);
					obj["functions"] = serializeList<Function>(m_data.functions);
					obj["methods"] = serializeList<Function>(m_data.methods);
				}

				void ObjectType::_deserialize(const QJsonObject& obj)
				{
					m_data.description = obj["description"].toString();
					m_data.index = obj["index"].toInt();
					m_data.listIndex = obj["listIndex"].toInt();
					foreach(auto classe, obj["classes"].toArray()) {
						m_data.classes.append(deserialize(classe.toObject()));
					}
					foreach(auto variable, obj["variables"].toArray()) {
						m_data.variables.append(Variable::deserialize(variable.toObject()));
					}
					foreach(auto attribute, obj["attributes"].toArray()) {
						m_data.attributes.append(Variable::deserialize(attribute.toObject()));
					}
					foreach(auto enumobj, obj["enums"].toArray()) {
						m_data.enums.append(EnumType::deserialize(enumobj.toObject()));
					}
					foreach(auto listobj, obj["listobjs"].toArray()) {
						m_data.listobjs.append(ListType::deserialize(listobj.toObject()));
					}
					foreach(auto function, obj["functions"].toArray()) {
						m_data.methods.append(Function::deserialize(function.toObject()));
					}
					foreach(auto method, obj["methods"].toArray()) {
						m_data.methods.append(Function::deserialize(method.toObject()));
					}
				}

				const data::ObjectType& ObjectType::data() const
				{
					return m_data;
				}

				bool ObjectType::setData(const data::ObjectType& data)
				{
					if (m_data == data)
						return false;
					m_data = data;
					return true;
				}

				int ObjectType::index() const
				{
					return m_data.index;
				}

				bool ObjectType::setIndex(int index)
				{
					if (m_data.index == index)
						return false;
					m_data.index = index;
					return true;
				}

				int ObjectType::listIndex() const
				{
					return m_data.listIndex;
				}

				bool ObjectType::setListIndex(int listIndex)
				{
					if (m_data.listIndex == listIndex)
						return false;
					m_data.listIndex = listIndex;
					return true;
				}

				const QString& ObjectType::description() const
				{
					return m_data.description;
				}

				bool ObjectType::setDescription(const QString& description)
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
