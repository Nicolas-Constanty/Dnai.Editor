#ifndef DNAI_COMMANDS_CORE_REMOVE_H
#define DNAI_COMMANDS_CORE_REMOVE_H

#include "dnai/corepackages/commands/declarator/remove.h"
#include "dnai/corepackages/commands/declarator/declare.h"
#include "dnai/commands/corecommand.h"
#include "dnai/models/core/entity.h"

namespace dnai
{
    using namespace corepackages;

    namespace commands
    {
        class RemoveCoreCommand : public CoreCommand<declarator::Remove, declarator::Declare>
        {
        public:
            RemoveCoreCommand(models::core::Entity const &entity);
            virtual ~RemoveCoreCommand() = default;
        };
    }
}

#endif // DNAI_COMMANDS_CORE_REMOVE_H
