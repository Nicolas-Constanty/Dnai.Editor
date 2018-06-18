#include <functional>

#include "dnai/core/objecthandler.h"

#include "dnai/commands/commandmanager.h"
#include "dnai/commands/corecommand.h"

#include "dnai/core/handlermanager.h"

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
            QObject::connect(HandlerManager::Instance().function(), SIGNAL(parameterSet(models::Entity*,QString)),
                             this,      SLOT(onParameterSet(models::Entity*,QString)));
            QObject::connect(&manager,  SIGNAL(entityRemoved(::core::EntityID,models::Entity&)),
                             this,      SLOT(onEntityRemoved(::core::EntityID,models::Entity&)));

            core::object::onAttributeAdded(std::bind(&ObjectHandler::onAttributeAdded, this, _1, _2, _3, _4));
            core::object::onAddAttributeError(std::bind(&ObjectHandler::onAddAttributeError, this, _1, _2, _3, _4, _5));

            core::object::onAttributeRemoved(std::bind(&ObjectHandler::onAttributeRemoved, this, _1, _2));
            core::object::onRemoveAttributeError(std::bind(&ObjectHandler::onRemoveAttributeError, this, _1, _2, _3));

            core::object::onAttributeRenamed(std::bind(&ObjectHandler::onAttributeRenamed, this, _1, _2, _3));
            core::object::onRenameAttributeError(std::bind(&ObjectHandler::onRenameAttributeError, this, _1, _2, _3, _4));

            core::object::onFunctionSetAsMember(std::bind(&ObjectHandler::onFunctionSetAsMember, this, _1, _2, _3));
            core::object::onSetFunctionAsMemberError(std::bind(&ObjectHandler::onSetFunctionAsMemberError, this, _1, _2, _3));
        }

        void ObjectHandler::onEntityAdded(EntityID id, models::Entity &entity)
        {
            switch (static_cast<ENTITY>(entity.entityType()))
            {
            case ENTITY::OBJECT_TYPE: {
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
                break;
            }
            case ENTITY::FUNCTION: {
                if (static_cast<ENTITY>(entity.parentItem()->entityType()) == ENTITY::OBJECT_TYPE)
                {
                    models::ObjectType *data = entity.parentItem()->guiModel<models::ObjectType>();

                    if (!data->hasFunction(entity.name()))
                    {
                        data->addFunction(entity.name());
                    }
                }
                break;
            }
            default:
                break;
            }

            refreshPendingAttributes(id);
        }

        void ObjectHandler::onEntityRemoved(EntityID id, models::Entity &entity)
        {
            if (static_cast<ENTITY>(entity.entityType()) == ENTITY::VARIABLE
                && static_cast<ENTITY>(entity.parentItem()->entityType()) == ENTITY::FUNCTION
                && static_cast<ENTITY>(entity.parentItem()->parentItem()->entityType()) == ENTITY::OBJECT_TYPE
                && entity.name() == "this")
            {
                models::ObjectType *data = entity.parentItem()->parentItem()->guiModel<models::ObjectType>();

                data->setFunctionStatus(entity.parentItem()->name(), false);
                emit functionSetAsStatic(entity.parentItem()->parentItem(), entity.parentItem()->name());
            }
            if (static_cast<ENTITY>(entity.entityType()) == ENTITY::FUNCTION
                && static_cast<ENTITY>(entity.parentItem()->entityType()) == ENTITY::OBJECT_TYPE)
            {
                models::ObjectType *data = entity.parentItem()->guiModel<models::ObjectType>();

                data->removeFunction(entity.name());
            }
        }

        void ObjectHandler::onParameterSet(models::Entity *func, QString paramName)
        {
            if (static_cast<ENTITY>(func->parentItem()->entityType()) == ENTITY::OBJECT_TYPE && paramName == "this")
            {
                models::ObjectType *data = func->parentItem()->guiModel<models::ObjectType>();

                data->setFunctionStatus(func->name(), true);
                emit functionSetAsMember(func->parentItem(), func->name(), func->findByName(paramName));
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

        void ObjectHandler::renameAttribute(quint32 obj, QString name, QString newName, bool save)
        {
            qDebug() << "==Core== Class.RenameAttribute(" << obj << ", " << name << ", " << newName << ") => save(" << save << ")";

            models::Entity &object = manager.getEntity(obj);

            commands::CommandManager::Instance()->exec(new commands::CoreCommand("Class.RenameAttribute", save,
                [&object, name, newName]() {
                    core::object::renameAttribtue(object.id(), name, newName);
                },
                [&object, name, newName]() {
                    core::object::renameAttribtue(object.id(), newName, name);
                }
            ));
        }

        void ObjectHandler::setAttributeType(quint32 obj, QString name, quint32 typ, bool save)
        {
            models::Entity &object = manager.getEntity(obj);
            models::ObjectType *data = object.guiModel<models::ObjectType>();
            models::Entity &type = manager.getEntity(data->getAttribute(name));
            models::Entity &newType = manager.getEntity(typ);

            commands::CommandManager::Instance()->exec(new commands::CoreCommand("Class.SetAttributeType", save,
                [this, &object, &newType, name]() {
                    m_pendingAdd.push([&object, name, &newType]() {
                        core::object::addAttribute(object.id(), name, newType.id(), VISIBILITY::PUBLIC);
                    });
                    core::object::removeAttribute(object.id(), name);
                },
                [this, &object, &type, name]() {
                    m_pendingAdd.push([&object, name, &type](){
                        core::object::addAttribute(object.id(), name, type.id(), VISIBILITY::PUBLIC);
                    });
                    core::object::removeAttribute(object.id(), name);
                }
            ));
        }

        void ObjectHandler::setFunctionAsMember(quint32 obj, QString name, bool save)
        {
            models::Entity &object = manager.getEntity(obj);
            models::Entity *func = object.findByName(name);

            qDebug() << "==Core== Class.SetFunctionAsMember(" << obj << ", " << name << ") => save(" << save << ")";

            if (func == nullptr)
                throw new std::out_of_range("No such function named " + name.toStdString());

            commands::CommandManager::Instance()->exec(new commands::CoreCommand("Class.SetFunctionAsMember", save,
                [&object, &name, func]() {
                    HandlerManager::Instance().Function().pendingParameter(func->id(), "this");
                    core::object::setFunctionAsMember(object.id(), name);
                },
                [func]() {
                    HandlerManager::Instance().Function().pendindRemoveParam(func->id(), "this");
                    core::declarator::remove(func->id(), "this");
                }
            ));
        }

        void ObjectHandler::setFunctionAsStatic(quint32 obj, QString name, bool save)
        {
            models::Entity &object = manager.getEntity(obj);
            models::Entity *func = object.findByName(name);

            qDebug() << "==Core== Class.SetFunctionAsStatic(" << obj << ", " << name << ") => save(" << save << ")";

            if (func == nullptr)
                throw new std::out_of_range("No such function named " + name.toStdString());

            commands::CommandManager::Instance()->exec(new commands::CoreCommand("Class.SetFunctionAsStatic", save,
                [func]() {
                    HandlerManager::Instance().Function().pendindRemoveParam(func->id(), "this");
                    core::declarator::remove(func->id(), "this");
                },
                [&object, func, name]() {
                    HandlerManager::Instance().Function().pendingParameter(func->id(), "this");
                    core::object::setFunctionAsMember(object.id(), name);
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

        void ObjectHandler::refreshPendingAttributes(EntityID id)
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
            if (!m_pendingAdd.empty())
            {
                m_pendingAdd.front()();
                m_pendingAdd.pop();
            }
            else
            {
                commands::CoreCommand::Success();
            }
            emit attributeRemoved(&object, name);
        }

        void ObjectHandler::onRemoveAttributeError(EntityID obj, QString name, QString msg)
        {
            Q_UNUSED(obj)

            commands::CoreCommand::Error();
            Editor::instance().notifyError("Unable to remove attribute " + name + ": " + msg);
        }

        void ObjectHandler::onAttributeRenamed(EntityID obj, QString name, QString newName)
        {
            models::Entity &object = manager.getEntity(obj);
            models::ObjectType *data = object.guiModel<models::ObjectType>();

            qDebug() << "==Core== Class.AttributeRenamed(" << obj << ", " << name << ", " << newName << ")";
            data->renameAttribute(name, newName);
            commands::CoreCommand::Success();
            emit attributeRenamed(&object, name, newName);
        }

        void ObjectHandler::onRenameAttributeError(EntityID obj, QString name, QString newName, QString msg)
        {
            commands::CoreCommand::Error();
            Editor::instance().notifyError("Unable to rename attribute " + name + " into " + newName + ": " + msg);
        }

        void ObjectHandler::onFunctionSetAsMember(EntityID obj, QString name, EntityID thisId)
        {
            models::Entity &object = manager.getEntity(obj);
            models::ObjectType *data = object.guiModel<models::ObjectType>();
            models::Entity *func = object.findByName(name);

            qDebug() << "==Core== Class.FunctionSetAsMember(" << obj << ", " << name << ", " << thisId << ")";
            commands::CoreCommand::Success();
            HandlerManager::Instance().Declarator().onDeclared(func->id(), ENTITY::VARIABLE, "this", VISIBILITY::PUBLIC, thisId);
            HandlerManager::Instance().Variable().onTypeSet(thisId, object.id());
            HandlerManager::Instance().Function().onParameterSet(func->id(), "this");
            emit functionSetAsMember(&object, name, &manager.getEntity(thisId));
        }

        void ObjectHandler::onSetFunctionAsMemberError(EntityID obj, QString name, QString msg)
        {
            Q_UNUSED(obj)

            commands::CoreCommand::Error();
            Editor::instance().notifyError("Unable to set function " + name + " as member: " + msg);
        }
    }
}
