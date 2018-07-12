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
				Context::Context(QObject* parent) : QObject(parent)
                {}

				const QList<declarable::Context*> &Context::contexts() const
				{
					return m_data.contexts;
				}
				const QList<declarable::ObjectType*> &Context::classes() const
				{
					return m_data.classes;
				}
				const QList<declarable::Variable*> &Context::variables() const
				{
					return m_data.variables;
				}
				const QList<declarable::EnumType*> &Context::enums() const
				{
					return m_data.enums;
				}
				const QList<declarable::ListType*> &Context::listobjs() const
				{
					return m_data.listobjs;
				}
				const QList<declarable::Function*> &Context::functions() const
				{
					return m_data.functions;
				}
				void Context::serialize(QJsonObject& obj) const
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
					obj["contexts"] = mergeArray(serializeList<Context>(m_data.contexts), obj["contexts"].toArray());
					obj["classes"] = mergeArray(serializeList<ObjectType>(m_data.classes), obj["classes"].toArray());
					obj["variables"] = mergeArray(serializeList<Variable>(m_data.variables), obj["variables"].toArray());
					obj["enums"] = mergeArray(serializeList<EnumType>(m_data.enums), obj["enums"].toArray());
					obj["listobjs"] = mergeArray(serializeList<ListType>(m_data.listobjs), obj["listobjs"].toArray());
					obj["functions"] = mergeArray(serializeList<Function>(m_data.functions), obj["functions"].toArray());*/
				}

				void Context::_deserialize(const QJsonObject& obj)
				{
					Entity::_deserialize(obj);
					/*foreach(auto context, obj["contexts"].toArray()) {
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
					}*/
				}
			}
		}
	}
}
