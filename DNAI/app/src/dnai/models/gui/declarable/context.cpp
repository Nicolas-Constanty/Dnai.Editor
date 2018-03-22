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
				void Context::serialize(QJsonObject& obj) const
				{
					Entity::serialize(obj);
					obj["contexts"] = serializeList<Context>(m_data.contexts);
					obj["classes"] = serializeList<ObjectType>(m_data.classes);
					obj["variables"] = serializeList<Variable>(m_data.variables);
					obj["enums"] = serializeList<EnumType>(m_data.enums);
					obj["listobjs"] = serializeList<ListType>(m_data.listobjs);
					obj["functions"] = serializeList<Function>(m_data.functions);
				}

				void Context::_deserialize(const QJsonObject& obj)
				{
					Entity::_deserialize(obj);
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
			}
		}
	}
}
