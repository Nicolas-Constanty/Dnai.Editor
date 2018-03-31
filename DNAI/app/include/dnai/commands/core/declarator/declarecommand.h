#ifndef DNAI_COMMANDS_CORE_DECLARATOR_DECLARE_H
#define DNAI_COMMANDS_CORE_DECLARATOR_DECLARE_H

#include "dnai/models/entity.h"
#include "dnai/commands/corecommand.h"

namespace dnai
{
    namespace commands
    {
        namespace declarator
        {
            class DeclareCommand : public CoreCommand
            {
            public:
                DeclareCommand(const models::Entity &entity);
                virtual ~DeclareCommand() = default;
            };
        }
    }
}

#endif // DNAI_COMMANDS_CORE_DECLARATOR_DECLARE_H
