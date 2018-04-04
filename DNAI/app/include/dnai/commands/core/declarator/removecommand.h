#ifndef DNAI_COMMANDS_CORE_DECLARATOR_REMOVECOMMAND_H
#define DNAI_COMMANDS_CORE_DECLARATOR_REMOVECOMMAND_H

#include "dnai/commands/corecommand.h"
#include "dnai/models/entity.h"

namespace dnai
{
    namespace commands
    {
        namespace declarator
        {
            class RemoveCommand : public CoreCommand
            {
            public:
                RemoveCommand(const models::Entity &entity);
                virtual ~RemoveCommand() = default;
            };
        }
    }
}

#endif // DNAI_COMMANDS_CORE_DECLARATOR_REMOVECOMMAND_H
