#include <functional>

#include "dnai/commands/commandmanager.h"
#include "dnai/commands/corecommand.h"

#include "dnai/core/listhandler.h"

#include "dnai/editor.h"

using namespace std::placeholders;

namespace dnai
{
    namespace gcore
    {
        ListHandler::ListHandler(EntityManager &manager) :
            manager(manager)
        {

        }

        void ListHandler::setup()
        {
            QObject::connect(&manager,  SIGNAL(entityAdded(::core::EntityID,models::Entity&)),
                             this,      SLOT(onEntityAdded(::core::EntityID,models::Entity&)));

            core::list::onTypeSet(std::bind(&ListHandler::onTypeSet, this, _1, _2));
            core::list::onSetTypeError(std::bind(&ListHandler::onSetTypeError, this, _1, _2, _3));
        }

        void ListHandler::onEntityAdded(EntityID id, models::Entity &entity)
        {
            if (static_cast<ENTITY>(entity.entityType()) == ENTITY::LIST_TYPE)
            {
                models::ListType *data = entity.guiModel<models::ListType>();

                if (!data->storedType().isNull())
                    pendingLists.push_back(&entity);
            }
            refreshTypes();
        }

        void ListHandler::refreshTypes()
        {
            for (std::list<models::Entity *>::iterator it = pendingLists.begin(); it != pendingLists.end();)
            {
                models::ListType *data = (*it)->guiModel<models::ListType>();

                if (manager.contains(data->storedType()))
                {
                    setType((*it)->id(), manager.getEntity(data->storedType())->id(), false);
                    it = pendingLists.erase(it);
                }
                else
                {
                    ++it;
                }
            }
        }

        void ListHandler::setType(quint32 listId, quint32 listType, bool save)
        {
            qDebug() << "==Core== List.SetType(" << listId << ", " << listType << ") => save(" << save << ")";

            models::Entity &listEntity = manager.getEntity(listId);
            models::ListType *data = listEntity.guiModel<models::ListType>();
            models::Entity &type = manager.getEntity(listType);
            models::Entity *oldType = nullptr;

            if (!data->storedType().isNull())
                oldType = manager.getEntity(data->storedType());

            commands::CommandManager::Instance()->exec(new commands::CoreCommand("List.SetType", save,
                [&listEntity, &type]() {
                    core::list::setType(listEntity.id(), type.id());
                },
                [&listEntity, oldType]() {
                    if (oldType != nullptr)
                        core::list::setType(listEntity.id(), oldType->id());
                }
            ));
        }

        void ListHandler::onTypeSet(EntityID listId, EntityID listType)
        {
            qDebug() << "==Core== List.TypeSet(" << listId << ", " << listType << ")";

            models::Entity &listEnt = manager.getEntity(listId);
            models::ListType *data = listEnt.guiModel<models::ListType>();
            models::Entity &type = manager.getEntity(listType);

            commands::CoreCommand::Success();
            data->setStoredType(type.guid());
            emit typeSet(&listEnt, &type);
        }

        void ListHandler::onSetTypeError(EntityID listId, EntityID listType, QString msg)
        {
            Q_UNUSED(listId)
            Q_UNUSED(listType)

            commands::CoreCommand::Error();
            Editor::instance().notifyError("Unable to set list type: " + msg);
        }
    }
}
