#include "dnai/commands/core/declare.h"
#include "dnai/controllers/clientcontroller.h"

namespace dnai
{
    namespace commands
    {
        DeclareCoreCommand::DeclareCoreCommand(const models::core::Entity &entity) :
            CoreCommand(
                new declarator::Declare(entity.containerId(), entity.entityType(), entity.name(), entity.visibility()),
                new declarator::Remove(entity.containerId(), entity.name()),
                true)
        {

        }
    }
}
