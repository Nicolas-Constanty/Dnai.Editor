#include <functional>

#include <QDebug>

#include "core.h"

#include "dnai/core/declaratorhandler.h"

#include "dnai/commands/corecommand.h"

#include "dnai/commands/commandmanager.h"

#include "dnai/editor.h"

#include "dnai/models/gui/entitylist.h"

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
            QObject::connect(&manager,  SIGNAL(entityAdded(::core::EntityID,models::Entity&)),
                             this,      SLOT(onEntityAdded(::core::EntityID,models::Entity&)));
            QObject::connect(&manager,  SIGNAL(entityRemoved(::core::EntityID,models::Entity&)),
                             this,      SLOT(onEntityRemoved(::core::EntityID,models::Entity&)));

            ::core::declarator::onDeclared(std::bind(&DeclaratorHandler::onDeclared, this, _1, _2, _3, _4, _5));
            ::core::declarator::onDeclareError(std::bind(&DeclaratorHandler::onDeclareError, this, _1, _2, _3, _4, _5));

            ::core::declarator::onRemoved(std::bind(&DeclaratorHandler::onRemoved, this, _1, _2, _3));
            ::core::declarator::onRemoveError(std::bind(&DeclaratorHandler::onRemoveError, this, _1, _2, _3));

            ::core::declarator::onRenamed(std::bind(&DeclaratorHandler::onRenamed, this, _1, _2, _3));
            ::core::declarator::onRenameError(std::bind(&DeclaratorHandler::onRenameError, this, _1, _2, _3, _4));

            ::core::declarator::onVisibilitySet(std::bind(&DeclaratorHandler::onVisibilitySet, this, _1, _2, _3));
            ::core::declarator::onSetVisibilityError(std::bind(&DeclaratorHandler::onSetVisibilityError, this, _1, _2, _3, _4));
        }

        void DeclaratorHandler::onEntityAdded(::core::EntityID id, models::Entity &entity)
        {
            for (models::Entity *child : entity.childrenItem())
            {
                child->setContainerId(id);
                pendingDeclaration.push(child);
                declare(id, child->entityType(), child->name(), static_cast<qint32>(child->visibility()), false);
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
			const auto entity = new models::Entity(new models::gcore::Entity(type), parent, guidata);
			if (static_cast<ENTITY>(parent->entityType()) != ENTITY::FUNCTION
				&& type == ENTITY::VARIABLE)
			{
				models::gui::declarable::Variable::variables()->append(entity);
			}
        	return entity;
        }

        void DeclaratorHandler::declare(quint32 parentId, qint32 type, QString name, qint32 visibility, bool save)
        {
            if (parentId != ::core::UNDEFINED_ID)
            {
                qDebug() << "==Core== Declarator.Declare("
                         << parentId << ", "
                         << static_cast<::core::ENTITY>(type) << ", "
                         << name << ", "
                         << static_cast<core::VISIBILITY>(visibility) << ") => save(" << save << ")";

                models::Entity *parent = &manager.getEntity(parentId);

                commands::CommandManager::Instance()->exec(
                    new commands::CoreCommand("Declarator.Declare", save,
                        /*
                         * Execute
                         */
                        [parent, type, name, visibility]() {
                            ::core::declarator::declare(parent->id(), static_cast<::core::ENTITY>(type), name, static_cast<::core::VISIBILITY>(visibility));
                        },
                        /*
                         * Un-execute
                         */
                        [parent, name]() {
                            ::core::declarator::remove(parent->id(), name);
                        }
                ));
            }
            else
            {
                qWarning() << "==Core== Declarator.Declare: Cannot declare an entity into parent that have invalid id: " << parentId;
            }
        }

        void DeclaratorHandler::remove(quint32 parentId, QString const &name, bool save)
        {
            models::Entity *torm = findEntity(parentId, name);

            if (torm == nullptr)
            {
                qWarning() << "==Core== Declarator.Remove: No such entity " << name << " in EntityManager";
                return;
            }

            models::Entity *parent = &manager.getEntity(parentId);
            ::core::ENTITY type = static_cast<::core::ENTITY>(torm->entityType());
            ::core::VISIBILITY visi = static_cast<::core::VISIBILITY>(torm->visibility());

            qDebug() << "==Core== Declarator.Remove(" << parentId << ", " << name << ") => save(" << save << ")";

            commands::CommandManager::Instance()->exec(
                new commands::CoreCommand("Declarator.Remove", save,
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

        void DeclaratorHandler::move(const models::Entity &tomove, const models::Entity &newparent, bool save)
        {
            Q_UNUSED(tomove)
            Q_UNUSED(newparent)
            Q_UNUSED(save)
        }

        void DeclaratorHandler::rename(quint32 parentId, QString const &name, QString const &newname, bool save)
        {
            models::Entity &decl = manager.getEntity(parentId);

            qDebug() << "==Core== Declarator.Rename(" << parentId << ", " << name << ", " << newname << ") => save(" << save << ")";
            commands::CommandManager::Instance()->exec(
                new commands::CoreCommand("Declarator.Rename", save,
                [&decl, name, newname]() {
                    core::declarator::rename(decl.id(), name, newname);
                },
                [&decl, name, newname]() {
                    core::declarator::rename(decl.id(), newname, name);
                }
            ));
        }

        void DeclaratorHandler::setVisibility(quint32 parentId, QString const &name, qint32 visibility, bool save)
        {
            models::Entity &decl = manager.getEntity(parentId);
            qint32 oldvisi = decl.visibility();

            qDebug() << "==Core== Declarator.SetVisibility(" << parentId << ", " << name << ", " << visibility << ") => save(" << save << ")";
            commands::CommandManager::Instance()->exec(
                new commands::CoreCommand("Declarator.SetVisibility", save,
                [&decl, name, visibility](){
                    core::declarator::setVisibility(decl.id(), name, static_cast<core::VISIBILITY>(visibility));
                },
                [&decl, name, oldvisi]() {
                    core::declarator::setVisibility(decl.id(), name, static_cast<core::VISIBILITY>(oldvisi));
                }
            ));
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

            qDebug() << "==Core== Declarator.Declared("
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
            Q_UNUSED(declarator)
            Q_UNUSED(name)
            Q_UNUSED(type)
            Q_UNUSED(visibility)

            if (!pendingDeclaration.empty())
            {
                pendingDeclaration.pop();
            }

            /*
             * todo: Implement a system to check if the command send corresponds to the event received
             */
            commands::CoreCommand::Error();
            qDebug() << "Failed to declare entity " << name << ": " << message;
            Editor::instance().notifyError("Unable to declare entity " + name + ": " + message);
        }

        void DeclaratorHandler::onRemoved(::core::EntityID declarator, const QString &name, std::list<EntityID> const &rmvList)
        {
            models::Entity *torm = findEntity(declarator, name);

            if (torm != nullptr)
            {
                commands::CoreCommand::Success();

                qDebug() << "==Core== Declarator.Removed(" << declarator << ", " << name << ", " << QList<EntityID>::fromStdList(rmvList) << ")";

                for (auto i = rmvList.rbegin(); i != rmvList.rend(); i++) {
                    int id = *i;
                    models::Entity &rmd = manager.getEntity(id);

                    //this will trigger onEntityRemoved
                    manager.removeEntity(id);

                    emit removed(&rmd);
                }
            }
        }

        void DeclaratorHandler::onRemoveError(::core::EntityID declarator, const QString &name, const QString &message)
        {
            if (findEntity(declarator, name) != nullptr)
            {
                commands::CoreCommand::Error();
                Editor::instance().notifyError("Unable to remove entity " + name + ": " + message);
            }
        }

        void DeclaratorHandler::onRenamed(EntityID declarator, const QString &name, const QString &newname)
        {
            models::Entity *entity = findEntity(declarator, name);

            if (entity != nullptr)
            {
                qDebug() << "==Core== Declarator.Renamed(" << declarator << ", " << name << ", " << newname <<  ")";
                entity->setName(newname);
                commands::CoreCommand::Success();
                emit renamed(entity, name, newname);
            }
        }

        void DeclaratorHandler::onRenameError(EntityID declarator, const QString &name, const QString &newname, const QString &message)
        {
            Q_UNUSED(declarator)
            Q_UNUSED(name)
            Q_UNUSED(newname)

            commands::CoreCommand::Error();
            Editor::instance().notifyError("Unable to rename entity " + name + ": " + message);
        }

        void DeclaratorHandler::onVisibilitySet(EntityID declarator, const QString &name, VISIBILITY visibility)
        {
            models::Entity *entity = findEntity(declarator, name);

            if (entity != nullptr)
            {
                qDebug() << "==Core== Declarator.VisibilitySet(" << declarator << ", " << name << ", " << visibility << ")";
                entity->setVisibility(static_cast<qint32>(visibility));
                commands::CoreCommand::Success();
            }
        }

        void DeclaratorHandler::onSetVisibilityError(EntityID declarator, const QString &name, VISIBILITY visibility, const QString &message)
        {
            Q_UNUSED(declarator)
            Q_UNUSED(name)
            Q_UNUSED(visibility)

            commands::CoreCommand::Error();
            Editor::instance().notifyError("Unable to set visibility of entity " + name + ": " + message);
        }
    }
}
