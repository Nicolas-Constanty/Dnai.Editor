#include "core.h"
#include "dnai/commands/core/declarator/declarecommand.h"

namespace dnai
{
    namespace commands
    {
        namespace declarator
        {
            DeclareCommand::DeclareCommand(const models::Entity &entity) :
                CoreCommand(
                    "CoreDeclare", true,
                    [&entity]() {
                        core::declarator::declare(
                                entity.containerId(),
                                static_cast<enums::core::ENTITY>(entity.entityType()),
                                entity.name(),
                                entity.visibility());
                    },
                    [&entity]() {
                        core::declarator::remove(entity.containerId(), entity.name());
                    }
                )
            {

            }
        }
    }
}
