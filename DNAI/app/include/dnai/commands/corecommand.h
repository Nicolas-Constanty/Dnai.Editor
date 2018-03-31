#ifndef DNAI_COMMANDS_CORECOMMAND_H
#define DNAI_COMMANDS_CORECOMMAND_H

#include <functional>

#include "command.h"

namespace dnai
{
    namespace commands
    {
        class CoreCommand : public Command
        {
        public:
            using Event = std::function<void()>;

        public:
            CoreCommand(QString const &name, bool save, Event const &exec, Event const &undo);
            virtual ~CoreCommand() = default;

        public:
            void execute() const override;
            void executeSave() override;
            void unExcute() const override;

        private:
            Event exec;
            Event undo;
        };
    }
}

#endif // DNAI_COMMANDS_CORECOMMAND_H
