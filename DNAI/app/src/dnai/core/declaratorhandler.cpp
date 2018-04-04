#include <functional>

#include <qDebug>

#include "dnai/core/declaratorhandler.h"

#include "dnai/commands/corecommand.h"
#include "dnai/commands/core/declarator/declarecommand.h"
#include "dnai/commands/core/declarator/removecommand.h"

#include "dnai/commands/commandmanager.h"

using namespace std::placeholders;

namespace dnai
{
    namespace core
    {
        DeclaratorHandler::DeclaratorHandler(EntityManager &manager) :
            manager(manager)
        {

        }

        void DeclaratorHandler::setup()
        {
            QObject::connect(&manager,  SIGNAL(entityAdded(enums::core::EntityID,models::Entity&)),
                             this,      SLOT(onEntityAdded(enums::core::EntityID,models::Entity&)));
            QObject::connect(&manager,  SIGNAL(entityRemoved(enums::core::EntityID,models::Entity&)),
                             this,      SLOT(onEntityRemoved(enums::core::EntityID,models::Entity&)));

            ::core::declarator::onDeclared([this](auto ... args){
                this->onDeclared(args...);
            });
            ::core::declarator::onDeclareError(std::bind(&DeclaratorHandler::onDeclareError, this, _1, _2, _3, _4, _5));
            ::core::declarator::onRemoved(std::bind(&DeclaratorHandler::onRemoved, this, _1, _2));
            ::core::declarator::onRemoveError(std::bind(&DeclaratorHandler::onRemoveError, this, _1, _2, _3));
        }

        void DeclaratorHandler::onEntityAdded(enums::core::EntityID id, models::Entity &entity)
        {
            for (models::Entity *child : entity.childrenItem())
            {
                child->setContainerId(id);
                declare(*child);
            }
        }

        void DeclaratorHandler::onEntityRemoved(enums::core::EntityID id, models::Entity &entity)
        {
            removed[entity.containerId()][entity.name().toStdString()] = &entity;
        }

        void DeclaratorHandler::declare(models::Entity &todeclare)
        {
            qDebug() << "Core: DeclaratorHandler: Declare("
                     << todeclare.containerId() << ", "
                     << todeclare.entityType() << ", "
                     << todeclare.name() << ", "
                     << todeclare.visibility() << ")";
            if (todeclare.containerId() != enums::core::UNDEFINED_ID)
            {
                commands::CommandManager::Instance()->exec(new commands::declarator::DeclareCommand(todeclare));
                pendingDeclaration.push(&todeclare);
            }
        }

        void DeclaratorHandler::remove(const models::Entity &toremove)
        {
            qDebug() << "Core: DeclaratorHandler: Remove("
                     << toremove.containerId() << ", "
                     << toremove.name() << ")";
            commands::CommandManager::Instance()->exec(new commands::declarator::RemoveCommand(toremove));
        }

        models::Entity *DeclaratorHandler::popDeclared(enums::core::EntityID declarator, enums::core::ENTITY type, const QString &name)
        {
            models::Entity *todeclare = nullptr;

            if (pendingDeclaration.empty())
            {
                typename RemoveMap::iterator decl = removed.find(declarator);

                if (decl == removed.end())
                {
                    return nullptr;
                }

                typename DeclaratorMap::iterator it = decl->second.find(name.toStdString());

                if (it == decl->second.end())
                {
                    return nullptr;
                }

                todeclare = it->second;

                if (static_cast<enums::core::ENTITY>(todeclare->entityType()) != type)
                {
                    return nullptr;
                }

                decl->second.erase(it);
            }
            else
            {
                todeclare = pendingDeclaration.front();

                if (todeclare->containerId() != declarator
                    || static_cast<enums::core::ENTITY>(todeclare->entityType()) != type
                    || todeclare->name() != name)
                {
                    return nullptr;
                }

                pendingDeclaration.pop();
            }
            return todeclare;
        }

        models::Entity *DeclaratorHandler::findEntity(enums::core::EntityID declarator, const QString &name, bool pop)
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
                    if (pop)
                        decl.removeOne(child);
                    return child;
                }
            }
            return nullptr;
        }

        void DeclaratorHandler::onDeclared(enums::core::EntityID declarator, enums::core::ENTITY type, const QString &name, enums::core::VISIBILITY visibility, enums::core::EntityID declared)
        {
            models::Entity *todeclare = popDeclared(declarator, type, name);

            if (todeclare == nullptr)
            {
                /*
                 * If someone else declared an entity
                 */
                qDebug() << "Core: DeclaratorHandler: onDeclared: No such entity to declare";
                return;
            }

            commands::CoreCommand::Success();

            qDebug() << "Core: DeclaratorHandler: onDeclared("
                     << declarator << ", "
                     << type << ", "
                     << name << ", "
                     << visibility << ", "
                     << declared << ")";

            //this triggers a entityAdded signal that will call onEntityAdded slot
            manager.addEntity(declared, *todeclare);
        }

        void DeclaratorHandler::onDeclareError(enums::core::EntityID declarator, enums::core::ENTITY type, const QString &name, enums::core::VISIBILITY visibility, const QString &message)
        {
            if (popDeclared(declarator, type, name) == nullptr)
            {
                /*
                 * If someone else tryied to declare an entity
                 */
                return;
            }

            commands::CoreCommand::Error();

            qDebug() << "Core: DeclaratorHandler: onDeclareError: " << message;
        }

        void DeclaratorHandler::onRemoved(enums::core::EntityID declarator, const QString &name)
        {
            models::Entity *torm = findEntity(declarator, name, true);

            if (torm != nullptr)
            {
                commands::CoreCommand::Success();

                qDebug() << "Core: DeclaratorHandler: onRemoved("
                         << declarator << ", "
                         << name << ")";

                //this will trigger onEntityRemoved
                manager.removeEntity(torm->id());
            }
        }

        void DeclaratorHandler::onRemoveError(enums::core::EntityID declarator, const QString &name, const QString &message)
        {
            if (findEntity(declarator, name) != nullptr)
            {
                commands::CoreCommand::Error();
                qDebug() << "Core: DeclaratorHandler: onRemoveError: " << message;
            }
        }
    }
}
