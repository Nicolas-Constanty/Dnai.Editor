#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

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
                QStringList ObjectType::attributes()
                {
                    return m_data.attributes.keys();
                }

                void ObjectType::addAttribute(const QString &name, quint32 type)
                {
                    if (m_data.attributes.contains(name) && m_data.attributes[name] == type)
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

                quint32 ObjectType::getAttribute(QString name) const
                {
                    return m_data.attributes.value(name);
                }

                QList<QVariant> ObjectType::functions() const
                {
                    QList<QVariant> toret;

                    for (std::pair<QString, bool> const &curr : m_data.functions.toStdMap())
                    {
                        toret.append(QVariant::fromValue(QPair<QString, bool>(curr.first, curr.second)));
                    }
                    return toret;
                }

                void ObjectType::addFunction(const QString &name)
                {
                    if (m_data.functions.contains(name))
                        return;
                    m_data.functions[name] = false;
                    emit functionsChanged(functions());
                }

                void ObjectType::removeFunction(const QString &name)
                {
                    if (!m_data.functions.contains(name))
                        return;
                    m_data.functions.remove(name);
                    emit functionsChanged(functions());
                }

                void ObjectType::setFunctionStatus(const QString &name, bool member)
                {
                    m_data.functions[name] = member;
                    emit functionsChanged(functions());
                }

                void ObjectType::serialize(QJsonObject &obj) const
                {
                    Entity::serialize(obj);

                    /*
                     * Attributes
                     */
                    QJsonArray attrs;
                    for (std::pair<QString, quint32> const &curr : m_data.attributes.toStdMap()) {
                        QJsonObject currAttr;

                        currAttr["key"] = curr.first;
                        currAttr["value"] = static_cast<qint32>(curr.second);
                        attrs.append(currAttr);
                    }
                    obj["attributes"] = attrs;
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
                            addAttribute(curr.toObject()["key"].toString(), curr.toObject()["value"].toInt());
                        }
                    }
                }
            }
		}
	}
}
