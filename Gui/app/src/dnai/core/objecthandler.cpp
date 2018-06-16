#include <functional>

#include "dnai/core/objecthandler.h"

#include "dnai/commands/commandmanager.h"
#include "dnai/commands/corecommand.h"

#include "dnai/editor.h"

using namespace std::placeholders;

namespace dnai
{
    namespace gcore
    {
        ObjectHandler::ObjectHandler(EntityManager &manager) :
            manager(manager)
        {

        }

        void ObjectHandler::setup()
        {
            QObject::connect(&manager,  SIGNAL(entityAdded(::core::EntityID,models::Entity&)),
                             this,      SLOT(onEntityAdded(::core::EntityID,models::Entity&)));

            core::object::onAttributeAdded(std::bind(&ObjectHandler::onAttributeAdded, this, _1, _2, _3, _4));
            core::object::onAddAttributeError(std::bind(&ObjectHandler::onAddAttributeError, this, _1, _2, _3, _4, _5));

            core::object::onAttributeRemoved(std::bind(&ObjectHandler::onAttributeRemoved, this, _1, _2));
            core::object::onRemoveAttributeError(std::bind(&ObjectHandler::onRemoveAttributeError, this, _1, _2, _3));
        }

        void ObjectHandler::onEntityAdded(EntityID id, models::Entity &entity)
        {
            if (static_cast<ENTITY>(entity.entityType()) == ENTITY::OBJECT_TYPE)
            {
                models::ObjectType *data = entity.guiModel<models::ObjectType>();
                QList<QString> pending;

                for (QString const &curr :  data->attributes())
                {
                    EntityID attrId = data->getAttribute(curr);

                    if (manager.contains(attrId))
                        addAttribute(id, curr, attrId, static_cast<qint32>(VISIBILITY::PUBLIC), false);
                    else
                        pending.append(curr);
                }
                if (!pending.isEmpty())
                    m_pendingAttributes[&entity] = pending;
            }
            else //refresh pending attributes
            {
                //for each object in map
                for (typename AttrMap::iterator currObjectIt = m_pendingAttributes.begin(); currObjectIt != m_pendingAttributes.end();)
                {
                    models::Entity *object = currObjectIt->first;
                    models::ObjectType *data = object->guiModel<models::ObjectType>();

                    QList<QString> &attrList = currObjectIt->second;

                    //for each attribute still waiting
                    for (QList<QString>::iterator attrIt = attrList.begin(); attrIt != attrList.end();)
                    {
                        QString &attr = *attrIt;
                        EntityID attrId = data->getAttribute(attr);

                        //if the attribute correspond to the entity added
                        if (attrId == id)
                        {
                            //add it
                            addAttribute(object->id(), attr, attrId, static_cast<qint32>(VISIBILITY::PUBLIC), false);
                            attrIt = attrList.erase(attrIt);
                        }
                        else
                        {
                            //either inc
                            ++attrIt;
                        }
                    }

                    //when there is no more pending attribute for this object
                    if (attrList.isEmpty())
                    {
                        //remove it from map
                        currObjectIt = m_pendingAttributes.erase(currObjectIt);
                    }
                    else
                    {
                        //either inc
                        ++currObjectIt;
                    }
                }
            }
        }

        void ObjectHandler::addAttribute(quint32 obj, QString name, quint32 typ, qint32 visi, bool save)
        {
            qDebug() << "==Core== Class.AddAttribute(" << obj << ", " << name << ", " << typ << ", " << visi << ") => save(" << save << ")";

            models::Entity &object = manager.getEntity(obj);
            models::Entity &type = manager.getEntity(typ);

            commands::CommandManager::Instance()->exec(new commands::CoreCommand("Class.AddAttribute", save,
                [&object, &type, name, visi]() {
                    core::object::addAttribute(object.id(), name, type.id(), static_cast<VISIBILITY>(visi));
                },
                [&object, name]() {
                    core::object::removeAttribute(object.id(), name);
                }
            ));
        }

        void ObjectHandler::removeAttribute(quint32 obj, QString name, bool save)
        {
            qDebug() << "==Core== Class.RemoveAttribute(" << obj << ", " << name << ") => save(" << save << ")";

            models::Entity &object = manager.getEntity(obj);
            models::ObjectType *data = object.guiModel<models::ObjectType>();
            models::Entity &typ = manager.getEntity(data->getAttribute(name));

            commands::CommandManager::Instance()->exec(new commands::CoreCommand("Class.RemoveAttribute", save,
                [&object, name]() {
                    core::object::removeAttribute(object.id(), name);
                },
                [&object, name, &typ]() {
                    core::object::addAttribute(object.id(), name, typ.id(), VISIBILITY::PUBLIC);
                }
            ));
        }


        bool ObjectHandler::isAttributePending(EntityID obj, QString const &name) const
        {
            return m_attributeAdded.find(std::to_string(obj) + name.toStdString()) != m_attributeAdded.end();
        }

        void ObjectHandler::removePendingAttribute(EntityID obj, QString const &name)
        {
            typename AttrSet::iterator it = m_attributeAdded.find(std::to_string(obj) + name.toStdString());

            m_attributeAdded.erase(it);
        }

        void ObjectHandler::onAttributeAdded(EntityID obj, QString name, EntityID typ, VISIBILITY visi)
        {
            models::Entity &object = manager.getEntity(obj);
            models::ObjectType *data = object.guiModel<models::ObjectType>();
            models::Entity &type = manager.getEntity(typ);

            qDebug() << "==Core== Class.AttributeAdded(" << obj << ", " << name << ", " << typ << ", " << visi << ")";

            if (isAttributePending(obj, name))
            {
                removePendingAttribute(obj, name);
            }
            else
            {
                data->addAttribute(name, type.id());
            }
            commands::CoreCommand::Success();
            emit attributeAdded(&object, name, &type, visi);
        }

        void ObjectHandler::onAddAttributeError(EntityID obj, QString name, EntityID type, VISIBILITY visi, QString msg)
        {
            Q_UNUSED(obj)
            Q_UNUSED(type)
            Q_UNUSED(visi)

            if (isAttributePending(obj, name))
                removePendingAttribute(obj, name);
            commands::CoreCommand::Error();
            Editor::instance().notifyError("Unable to add attribute " + name + ": " + msg);
        }

        void ObjectHandler::onAttributeRemoved(EntityID obj, QString name)
        {
            models::Entity &object = manager.getEntity(obj);
            models::ObjectType *data = object.guiModel<models::ObjectType>();

            qDebug() << "==Core== Class.AttributeRemove(" << obj << ", " << name << ")";
            data->removeAttribute(name);
            commands::CoreCommand::Success();
            emit attributeRemoved(&object, name);
        }

        void ObjectHandler::onRemoveAttributeError(EntityID obj, QString name, QString msg)
        {
            Q_UNUSED(obj)

            commands::CoreCommand::Error();
            Editor::instance().notifyError("Unable to remove attribute " + name + ": " + msg);
        }
    }
}
