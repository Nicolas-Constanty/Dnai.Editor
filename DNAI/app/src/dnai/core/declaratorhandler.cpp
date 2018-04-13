#include <functional>

#include <QDebug>

#include "core.h"

#include "dnai/core/declaratorhandler.h"

#include "dnai/commands/corecommand.h"

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

            ::core::declarator::onDeclared(std::bind(&DeclaratorHandler::onDeclared, this, _1, _2, _3, _4, _5));
            ::core::declarator::onDeclareError(std::bind(&DeclaratorHandler::onDeclareError, this, _1, _2, _3, _4, _5));
            ::core::declarator::onRemoved(std::bind(&DeclaratorHandler::onRemoved, this, _1, _2));
            ::core::declarator::onRemoveError(std::bind(&DeclaratorHandler::onRemoveError, this, _1, _2, _3));
        }

        void DeclaratorHandler::onEntityAdded(enums::core::EntityID id, models::Entity &entity)
        {
            for (models::Entity *child : entity.childrenItem())
            {
                child->setContainerId(id);
                pendingDeclaration.push(child);
                declare(id, child->entityType(), child->name(), child->visibility());
            }
        }

        void DeclaratorHandler::onEntityRemoved(enums::core::EntityID id, models::Entity &entity)
        {
            removedMap[entity.containerId()][entity.name().toStdString()] = &entity;
        }

        models::Entity *DeclaratorHandler::createEntity(enums::core::ENTITY type, models::Entity *parent)
        {
            interfaces::IEntity *guidata = nullptr;

            switch (type) {
            case enums::core::ENTITY::CONTEXT:
                guidata = new models::gui::declarable::Context();
                break;
            case enums::core::ENTITY::VARIABLE:
                guidata = new models::gui::declarable::Variable();
                break;
            case enums::core::ENTITY::LIST_TYPE:
                guidata = new models::gui::declarable::ListType();
                break;
            case enums::core::ENTITY::OBJECT_TYPE:
                guidata = new models::gui::declarable::ObjectType();
                break;
            case enums::core::ENTITY::FUNCTION:
                guidata = new models::gui::declarable::Function();
                break;
            default:
                return nullptr;
            }

            return new models::Entity(new models::core::Entity(type), parent, guidata);
        }

        void DeclaratorHandler::declare(quint32 parentId, qint32 type, QString name, qint32 visibility)
        {
            if (parentId != enums::core::UNDEFINED_ID)
            {
                if (name.isEmpty())
                    name = "EmptyEntity(" + QString::number(qrand()) + ")";

                qDebug() << "core::declarator::declare("
                         << parentId << ", "
                         << static_cast<enums::core::ENTITY>(type) << ", "
                         << name << ", "
                         << enums::core::VISIBILITY::PUBLIC << ")";

                commands::CommandManager::Instance()->exec(
                    new commands::CoreCommand("Declarator.Declare", true,
                        /*
                         * Execute
                         */
                        std::bind(&::core::declarator::declare, parentId, static_cast<enums::core::ENTITY>(type), name, static_cast<enums::core::VISIBILITY>(visibility)),
                        /*
                         * Un-execute
                         */
                        std::bind(&::core::declarator::remove, parentId, name)));
            }
            else
            {
                qDebug() << "Cannot declare an entity into parent that have invalid id: " << parentId;
            }
        }

        void DeclaratorHandler::remove(const models::Entity *toremove)
        {
            enums::core::EntityID declarator = toremove->containerId();
            enums::core::ENTITY type = static_cast<enums::core::ENTITY>(toremove->entityType());
            QString name = toremove->name();
            enums::core::VISIBILITY visi = toremove->visibility();

            qDebug() << "Core: DeclaratorHandler: Remove("
                     << toremove->containerId() << ", "
                     << toremove->name() << ")";

            commands::CommandManager::Instance()->exec(
                new commands::CoreCommand("Declarator.Remove", true,
                    /*
                     * Execute
                     */
                    std::bind(&::core::declarator::remove, declarator, name),
                    /*
                     * Un-execute
                     */
                    std::bind(&::core::declarator::declare, declarator, type, name, visi)));
        }

        void DeclaratorHandler::move(const models::Entity &tomove, const models::Entity &newparent)
        {

        }

        void DeclaratorHandler::rename(const models::Entity &torename, const QString &newname)
        {

        }

        void DeclaratorHandler::setVisibility(const models::Entity &entity, enums::core::VISIBILITY visibility)
        {

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

        void DeclaratorHandler::onDeclared(enums::core::EntityID declarator, enums::core::ENTITY type, const QString &name, enums::core::VISIBILITY visibility, enums::core::EntityID declaredId)
        {
            models::Entity *todeclare = nullptr;

            if (!pendingDeclaration.empty()
                && pendingDeclaration.front()->containerId() == declarator
                && pendingDeclaration.front()->entityType() == type
                && pendingDeclaration.front()->name() == name
                && pendingDeclaration.front()->visibility() == visibility)
            {
                todeclare = pendingDeclaration.front();
                pendingDeclaration.pop();
            }
            else
            {
                todeclare = createEntity(type, &manager.getEntity(declarator));
                todeclare->setName(name);
                todeclare->setVisibility(visibility);
                todeclare->setEntityType(static_cast<qint32>(type));
                todeclare->setContainerId(declarator);
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

        void DeclaratorHandler::onDeclareError(enums::core::EntityID declarator, enums::core::ENTITY type, const QString &name, enums::core::VISIBILITY visibility, const QString &message)
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
