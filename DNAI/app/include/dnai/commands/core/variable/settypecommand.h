#ifndef DNAI_COMMANDS_CORE_VARIABLE_SETTYPECOMMAND_H
#define DNAI_COMMANDS_CORE_VARIABLE_SETTYPECOMMAND_H

#include "dnai/commands/corecommand.h"
#include "dnai/models/entity.h"

namespace dnai
{
    namespace commands
    {
        namespace variable
        {
            class SetTypeCommand : public CoreCommand
            {
            public:
                SetTypeCommand(const models::Entity &variable, const models::Entity &type);
                virtual ~SetTypeCommand() = default;

            private:
                enums::core::EntityID oldType;
            };
        }
    }
}

#endif // DNAI_COMMANDS_CORE_VARIABLE_SETTYPECOMMAND_H
