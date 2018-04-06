#include <functional>

#include "dnai/core/enumhandler.h"

#include "dnai/commands/commandmanager.h"
#include "dnai/commands/corecommand.h"

using namespace std::placeholders;

namespace dnai
{
    namespace core
    {
        EnumHandler::EnumHandler(EntityManager &manager) :
            manager(manager)
        {

        }

        void EnumHandler::setup()
        {
            QObject::connect(&manager,  SIGNAL(entityAdded(enums::core::EntityID,models::Entity&)),
                             this,      SLOT(onEntityAdded(enums::core::EntityID,models::Entity&)));

            ::core::enumeration::onValueSet(std::bind(&EnumHandler::onValueSet, this, _1, _2));
            ::core::enumeration::onSetValueError(std::bind(&EnumHandler::onSetValueError, this, _1, _2, _3));
            ::core::enumeration::onValueRemoved(std::bind(&EnumHandler::onValueRemoved, this, _1, _2));
            ::core::enumeration::onRemoveValueError(std::bind(&EnumHandler::onRemoveValueError, this, _1, _2, _3));
        }

        void EnumHandler::onEntityAdded(enums::core::EntityID id, models::Entity &entity)
        {

        }

        void EnumHandler::setValue()
        {
            /*
            commands::CommandManager::Instance()->exec(
                new commands::CoreCommand("Enum.SetValue", true,
                    std::bind(::core::enumeration::setValue(...)),
                    std::bind(::core::enumeration::removeValue(...))
                )
            );
            */
        }

        void EnumHandler::removeValue()
        {
            /*
            commands::CommandManager::Instance()->exec(
                new commands::CoreCommand("Enum.SetValue", true,
                    std::bind(::core::enumeration::removeValue(...)),
                    std::bind(::core::enumeration::setValue(...))
                )
            );
            */
        }

        void EnumHandler::onValueSet(enums::core::EntityID enumeration, const QString &name)
        {

        }

        void EnumHandler::onSetValueError(enums::core::EntityID enumeration, const QString &name, const QString &message)
        {

        }

        void EnumHandler::onValueRemoved(enums::core::EntityID enumeration, const QString &name)
        {

        }

        void EnumHandler::onRemoveValueError(enums::core::EntityID enumeration, const QString &name, const QString &message)
        {

        }
    }
}
