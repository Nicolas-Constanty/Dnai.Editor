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
				const QList<ObjectType *> &ObjectType::classes() const
				{
					return m_data.classes;
				}
				const QList<Variable *> &ObjectType::variables() const
				{
					return m_data.variables;
				}
				const QList<Variable *> &ObjectType::attributes() const
				{
					return m_data.attributes;
				}
				const QList<EnumType *> &ObjectType::enums() const
				{
					return m_data.enums;
				}
				const QList<ListType *> &ObjectType::listobjs() const
				{
					return m_data.listobjs;
				}
				const QList<Function *> &ObjectType::functions() const
				{
					return m_data.functions;
				}
				const QList<Function *> &ObjectType::methods() const
				{
					return m_data.methods;
				}
				void ObjectType::serialize(QJsonObject& obj) const
				{
					Entity::serialize(obj);
					/*const auto mergeArray = [](QJsonArray a1, QJsonArray a2) -> QJsonArray
					{
						auto i = 0;
						if (a1.count() != a2.count())
							return a1;
						for (auto o : a1)
						{
							auto v = o.toObject();
							auto v1 = a2[i].toObject();
							foreach(const QString& key, v1.keys()) {
								v[key] = v1.value(key);
							}
							o = v;
						}
						return a1;
					};
					obj["classes"] = mergeArray(serializeList<ObjectType>(m_data.classes), obj["classes"].toArray());
					obj["variables"] = mergeArray(serializeList<Variable>(m_data.variables), obj["variables"].toArray());
					obj["attributes"] = mergeArray(serializeList<Variable>(m_data.attributes), obj["attributes"].toArray());
					obj["enums"] = mergeArray(serializeList<EnumType>(m_data.enums), obj["enums"].toArray());
					obj["listobjs"] = mergeArray(serializeList<ListType>(m_data.listobjs), obj["listobjs"].toArray());
					obj["functions"] = mergeArray(serializeList<Function>(m_data.functions), obj["functions"].toArray());
					obj["methods"] = mergeArray(serializeList<Function>(m_data.methods), obj["methods"].toArray());*/
				}

				void ObjectType::_deserialize(const QJsonObject& obj)
				{
					Entity::_deserialize(obj);
					/*foreach(auto classe, obj["classes"].toArray()) {
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
					}*/
				}
			}
		}
	}
}
