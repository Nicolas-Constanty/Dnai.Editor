#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include "dnai/models/gui/declarable/objecttype.h"
#include "dnai/exceptions/notimplemented.h"
#include "dnai/core/handlermanager.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
            namespace declarable
            {
                QStringList ObjectType::attributes()
                {
                    return m_data.attributes.keys();
                }

                void ObjectType::addAttribute(const QString &name, QUuid const &type)
                {
                    if (m_data.attributes.contains(name) && type == m_data.attributes[name])
                        return;

                    m_data.attributes[name] = type;
                    emit attributesChanged(attributes());
                }

                void ObjectType::removeAttribute(const QString &name)
                {
                    if (!m_data.attributes.contains(name))
                        return;
                    m_data.attributes.remove(name);
                    emit attributesChanged(attributes());
                }

                void ObjectType::renameAttribute(const QString &name, const QString &newName)
                {
                    m_data.attributes[newName] = m_data.attributes[name];
                    m_data.attributes.remove(name);
                    emit attributesChanged(attributes());
                }

                QUuid ObjectType::getAttribute(QString name) const
                {
                    return m_data.attributes.value(name);
                }

                QStringList ObjectType::functions() const
                {
                    QStringList toret;

                    for (QUuid const &curr :  m_data.functions)
                    {
                        models::Entity *func = dnai::gcore::HandlerManager::Instance().getEntity(curr);

                        if (func != nullptr)
                            toret.append(func->name());
                    }
                    return toret;
                }

                void ObjectType::addFunction(const QUuid &funcUid)
                {
                    if (m_data.functions.contains(funcUid))
                        return;
                    m_data.functions.append(funcUid);
                    emit functionsChanged(functions());
                }

                void ObjectType::removeFunction(const QUuid &funcUid)
                {
                    if (!m_data.functions.contains(funcUid))
                        return;
                    m_data.functions.removeOne(funcUid);
                    emit functionsChanged(functions());
                }

                bool ObjectType::hasFunction(const QUuid &funcUid)
                {
                    return m_data.functions.contains(funcUid);
                }

                bool ObjectType::isFunctionMember(QString name) const
                {
                    for (QUuid const &curr : m_data.functions)
                    {
                        models::Entity *func = dnai::gcore::HandlerManager::Instance().getEntity(curr);

                        if (func != nullptr && func->name() == name)
                        {
                            models::Function *data = func->guiModel<models::Function>();

                            return data->hasInput("this"); //add the type of the object
                        }
                    }
                    return false;
                }

                void ObjectType::serialize(QJsonObject &obj) const
                {
                    Entity::serialize(obj);

                    /*
                     * Attributes
                     */
                    QJsonArray attrs;
                    for (std::pair<QString, QUuid> const &curr : m_data.attributes.toStdMap()) {
                        QJsonObject currAttr;

                        currAttr["key"] = curr.first;
                        currAttr["value"] = curr.second.toString();
                        attrs.append(currAttr);
                    }
                    obj["attributes"] = attrs;

                    /*
                     * Functions
                     */
                    QJsonArray funcs;
                    for (QUuid const &curr : m_data.functions)
                    {
                        funcs.append(curr.toString());
                    }
                    obj["functions"] = funcs;
                }

                void ObjectType::_deserialize(const QJsonObject &obj)
                {
                    Entity::_deserialize(obj);

                    /*
                     * Attributes
                     */
                    if (obj.contains("attributes"))
                    {
                        QJsonArray attrs = obj["attributes"].toArray();

                        for (QJsonValue const &curr : attrs)
                        {
                            addAttribute(curr.toObject()["key"].toString(), curr.toObject()["value"].toString());
                        }
                    }

                    /*
                     * Functions
                     */
                    if (obj.contains("functions"))
                    {
                        QJsonArray funcs = obj["functions"].toArray();

                        for (QJsonValue const &curr : funcs)
                        {
                            m_data.functions.append(curr.toString());
                        }
                    }
                }
            }
		}
	}
}
