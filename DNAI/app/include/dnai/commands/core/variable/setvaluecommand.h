#ifndef DNAI_COMMANDS_CORE_VARIABLE_SETVALUECOMMAND_H
#define DNAI_COMMANDS_CORE_VARIABLE_SETVALUECOMMAND_H

#include <QObject>

#include <QJsonObject>

#include "dnai/commands/corecommand.h"

#include "dnai/models/entity.h"

namespace dnai
{
    namespace commands
    {
        namespace variable
        {
            class SetValueCommand : public CoreCommand
            {
            public:
                SetValueCommand(models::Entity const &variable, QString const &oldValue);
                virtual ~SetValueCommand() = default;

            private:
                QString oldValue;
            };
        }
    }
}

#endif // DNAI_COMMANDS_CORE_VARIABLE_SETVALUECOMMAND_H
