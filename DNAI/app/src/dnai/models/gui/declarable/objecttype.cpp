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
				void ObjectType::serialize(QJsonObject& obj) const
				{
					Entity::serialize(obj);
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
					Entity::_deserialize(obj);
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
			}
		}
	}
}
