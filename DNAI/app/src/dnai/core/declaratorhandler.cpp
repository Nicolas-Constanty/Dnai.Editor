#include <functional>

#include <QDebug>

#include "core.h"

#include "dnai/core/declaratorhandler.h"

#include "dnai/commands/corecommand.h"

#include "dnai/commands/commandmanager.h"

using namespace std::placeholders;

namespace dnai
{
    namespace gcore
    {
        DeclaratorHandler::DeclaratorHandler(EntityManager &manager) :
            manager(manager)
        {

        }

        DeclaratorHandler::~DeclaratorHandler()
        {
            for (models::Entity &entity : manager)
            {
                delete &entity;
            }
            for (std::pair<const std::string, models::Entity *> &curr : removedEntities)
            {
                delete curr.second;
            }
        }

        void DeclaratorHandler::setup()
        {
            QObject::connect(&manager,  SIGNAL(entityAdded(enums::core::EntityID,models::Entity&)),
                             this,      SLOT(onEntityAdded(enums::core::EntityID,models::Entity&)));
            QObject::connect(&manager,  SIGNAL(entityRemoved(enums::core::EntityID,models::Entity&)),
                             this,      SLOT(onEntityRemoved(enums::core::EntityID,models::Entity&)));

            ::core::declarator::onDeclared(std::bind(&DeclaratorHandler::onDeclared, this, _1, _2, _3, _4, _5));
            ::core::declarator::onDeclareError(std::bind(&DeclaratorHandler::onDeclareError, this, _1, _2, _3, _4, _5));
            ::core::declarator::onRemoved(std::bind(&DeclaratorHandler::onRemoved, this, _1, _2));
            ::core::declarator::onRemoveError(std::bind(&DeclaratorHandler::onRemoveError, this, _1, _2, _3));
        }

        void DeclaratorHandler::onEntityAdded(::core::EntityID id, models::Entity &entity)
        {
            for (models::Entity *child : entity.childrenItem())
            {
                child->setContainerId(id);
                pendingDeclaration.push(child);
                declare(id, child->entityType(), child->name(), static_cast<qint32>(child->visibility()));
            }
        }

        void DeclaratorHandler::onEntityRemoved(::core::EntityID, models::Entity &entity)
        {
            removedEntities[entity.fullName().toStdString()] = &entity;
        }

        models::Entity *DeclaratorHandler::createEntity(::core::ENTITY type, models::Entity *parent)
        {
            interfaces::IEntity *guidata = nullptr;

            switch (type) {
            case ::core::ENTITY::CONTEXT:
                guidata = new models::gui::declarable::Context();
                break;
            case ::core::ENTITY::VARIABLE:
                guidata = new models::gui::declarable::Variable();
                break;
            case ::core::ENTITY::LIST_TYPE:
                guidata = new models::gui::declarable::ListType();
                break;
            case ::core::ENTITY::OBJECT_TYPE:
                guidata = new models::gui::declarable::ObjectType();
                break;
            case ::core::ENTITY::FUNCTION:
                guidata = new models::gui::declarable::Function();
                break;
            case ::core::ENTITY::ENUM_TYPE:
                guidata = new models::gui::declarable::EnumType();
                break;
            default:
                return nullptr;
            }

            return new models::Entity(new models::gcore::Entity(type), parent, guidata);
        }

        void DeclaratorHandler::declare(quint32 parentId, qint32 type, QString name, qint32 visibility)
        {
            if (parentId != ::core::UNDEFINED_ID)
            {
                qDebug() << "core::declarator::declare("
                         << parentId << ", "
                         << static_cast<::core::ENTITY>(type) << ", "
                         << name << ", "
                         << ::core::VISIBILITY::PUBLIC << ")";

                models::Entity *parent = &manager.getEntity(parentId);

                commands::CommandManager::Instance()->exec(
                    new commands::CoreCommand("Declarator.Declare", true,
                        /*
                         * Execute
                         */
                        [parent, type, name, visibility]() {
                            qDebug() << "Declare " << name << " into " << parent->name() << "(" << parent->id() << ")";
                            ::core::declarator::declare(parent->id(), static_cast<::core::ENTITY>(type), name, static_cast<::core::VISIBILITY>(visibility));
                        },
                        /*
                         * Un-execute
                         */
                        [parent, name]() {
                            qDebug() << "Remove " << name << " from " << parent->name() << "(" << parent->id() << ")";
                            ::core::declarator::remove(parent->id(), name);
                        }
                ));
            }
            else
            {
                qDebug() << "Cannot declare an entity into parent that have invalid id: " << parentId;
            }
        }

        void DeclaratorHandler::remove(quint32 parentId, QString const &name)
        {
            models::Entity *torm = findEntity(parentId, name);

            if (torm == nullptr)
            {
                qDebug() << "No such entity " << name << " in EntityManager";
                return;
            }

            models::Entity *parent = &manager.getEntity(parentId);
            ::core::ENTITY type = static_cast<::core::ENTITY>(torm->entityType());
            ::core::VISIBILITY visi = static_cast<::core::VISIBILITY>(torm->visibility());

            qDebug() << "Core: DeclaratorHandler: Remove(" << parentId << ", " << name << ")";

            commands::CommandManager::Instance()->exec(
                new commands::CoreCommand("Declarator.Remove", true,
                    /*
                     * Execute
                     */
                    [parent, name]() {
                        ::core::declarator::remove(parent->id(), name);
                    },
                    /*
                     * Un-execute
                     */
                    [parent, name, type, visi]() {
                        ::core::declarator::declare(parent->id(), type, name, visi);
                    }));
        }

        void DeclaratorHandler::move(const models::Entity &tomove, const models::Entity &newparent)
        {
            Q_UNUSED(tomove)
            Q_UNUSED(newparent)
        }

        void DeclaratorHandler::rename(const models::Entity &torename, const QString &newname)
        {
            Q_UNUSED(torename)
            Q_UNUSED(newname)
        }

        void DeclaratorHandler::setVisibility(const models::Entity &entity, ::core::VISIBILITY visibility)
        {
            Q_UNUSED(entity)
            Q_UNUSED(visibility)
        }

        models::Entity *DeclaratorHandler::findEntity(::core::EntityID declarator, const QString &name)
        {
            if (!manager.contains(declarator))
            {
                return nullptr;
            }

            models::Entity &decl = manager.getEntity(declarator);

            for (models::Entity *child : decl.childrenItem())
            {
                if (child->name() == name)
                {
                    return child;
                }
            }
            return nullptr;
        }

        void DeclaratorHandler::onDeclared(::core::EntityID declarator, ::core::ENTITY type, const QString &name, ::core::VISIBILITY visibility, ::core::EntityID declaredId)
        {
            models::Entity *todeclare = nullptr;

            if (!manager.contains(declarator))
                return;

            if (!pendingDeclaration.empty()
                && pendingDeclaration.front()->containerId() == declarator
                && pendingDeclaration.front()->entityType() == static_cast<qint32>(type)
                && pendingDeclaration.front()->name() == name
                && pendingDeclaration.front()->visibility() == static_cast<qint32>(visibility))
            {
                todeclare = pendingDeclaration.front();
                pendingDeclaration.pop();
            }
            else
            {
                models::Entity &parent = manager.getEntity(declarator);
                std::unordered_map<std::string, models::Entity *>::iterator it = removedEntities.find(parent.childFullName(name).toStdString());

                if (it != removedEntities.end())
                {
                    todeclare = it->second;
                    todeclare->setParent(&parent);
                    todeclare->setContainerId(declarator);
                    removedEntities.erase(it);
                }
                else
                {
                    todeclare = createEntity(type, &parent);
                    todeclare->setName(name);
                    todeclare->setVisibility(static_cast<qint32>(visibility));
                    todeclare->setEntityType(static_cast<qint32>(type));
                    todeclare->setContainerId(declarator);
                }
            }

            /*
             * todo: Implement a system to check if a the declared entity was declared by the gui
             */
            commands::CoreCommand::Success();

            qDebug() << "Core: DeclaratorHandler: onDeclared("
                     << declarator << ", "
                     << type << ", "
                     << name << ", "
                     << visibility << ", "
                     << declaredId << ")";

            todeclare->setId(declaredId);

            //this triggers a entityAdded signal that will call onEntityAdded slot
            manager.addEntity(declaredId, *todeclare);

            emit declared(todeclare);
        }

        void DeclaratorHandler::onDeclareError(::core::EntityID declarator, ::core::ENTITY type, const QString &name, ::core::VISIBILITY visibility, const QString &message)
        {
            if (!pendingDeclaration.empty())
            {
                pendingDeclaration.pop();
            }

            /*
             * todo: Implement a system to check if the command send corresponds to the event received
             */
            commands::CoreCommand::Error();

            qDebug() << "Core: DeclaratorHandler: onDeclareError: " << message;
        }

        void DeclaratorHandler::onRemoved(::core::EntityID declarator, const QString &name)
        {
            models::Entity *torm = findEntity(declarator, name);

            if (torm != nullptr)
            {
                commands::CoreCommand::Success();

                qDebug() << "Core: DeclaratorHandler: onRemoved("
                         << declarator << ", "
                         << name << ")";

                emit removed(torm);

                //this will trigger onEntityRemoved
                manager.removeEntity(torm->id());
            }
        }

        void DeclaratorHandler::onRemoveError(::core::EntityID declarator, const QString &name, const QString &message)
        {
            if (findEntity(declarator, name) != nullptr)
            {
                commands::CoreCommand::Error();
                qDebug() << "Core: DeclaratorHandler: onRemoveError: " << message;
            }
        }
    }
}
