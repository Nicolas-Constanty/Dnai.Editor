#include "dnai/commands/core/remove.h"

namespace dnai
{
    namespace commands
    {
        RemoveCoreCommand::RemoveCoreCommand(const models::core::Entity &entity) :
            CoreCommand<declarator::Remove, declarator::Declare>(
                new declarator::Remove(entity.containerId(), entity.name()),
                new declarator::Declare(entity.containerId(), entity.entityType(), entity.name(), entity.visibility()),
                true)
        {

        }
    }
}
