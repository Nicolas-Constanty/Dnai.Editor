#ifndef DNAI_COMMANDS_CORECOMMAND_H
#define DNAI_COMMANDS_CORECOMMAND_H

#include <functional>
#include <queue>

#include "command.h"
#include "core.h"

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

        private:
            static std::queue<CoreCommand *> commandQueue;

        public:
            static void Success();
            static void Error();
        };
    }
}

#endif // DNAI_COMMANDS_CORECOMMAND_H
