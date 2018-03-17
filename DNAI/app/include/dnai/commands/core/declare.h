#ifndef APP_DNAI_COMMANDS_CORE_DECLARE_H
#define APP_DNAI_COMMANDS_CORE_DECLARE_H

#include "dnai/commands/corecommand.h"
#include "dnai/corepackages/commands/declarator/declare.h"
#include "dnai/corepackages/commands/declarator/remove.h"
#include "dnai/models/core/entity.h"

namespace dnai
{
    using namespace enums::core;
    using namespace corepackages;

    namespace commands
    {
        class DeclareCoreCommand : public CoreCommand<declarator::Declare, declarator::Remove>
        {
        public:
            DeclareCoreCommand(const models::core::Entity &entity);
            virtual ~DeclareCoreCommand() = default;
        };
    }
}

#endif // APP_DNAI_COMMANDS_CORE_DECLARE_H
