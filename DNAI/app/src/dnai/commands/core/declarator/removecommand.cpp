#include "dnai/commands/core/declarator/removecommand.h"

namespace dnai
{
    namespace commands
    {
        namespace declarator
        {
            RemoveCommand::RemoveCommand(const models::Entity &entity) :
                CoreCommand(
                    "Declarator.Remove", true,
                    [&entity](){
                        core::declarator::remove(entity.containerId(), entity.name());
                    },
                    [&entity](){
                        core::declarator::declare(
                                entity.containerId(),
                                static_cast<enums::core::ENTITY>(entity.entityType()),
                                entity.name(),
                                entity.visibility());
                    })
            {

            }
        }
    }
}
