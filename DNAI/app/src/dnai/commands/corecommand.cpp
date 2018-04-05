#include "dnai/commands/corecommand.h"
#include "dnai/commands/commandmanager.h"

namespace dnai
{
    namespace commands
    {
        std::queue<CoreCommand *> CoreCommand::commandQueue;

        CoreCommand::CoreCommand(QString const &name, bool save, const Event &exec, const Event &undo) :
            Command(name, save),
            exec(exec),
            undo(undo)
        {

        }

        void CoreCommand::execute() const
        {
            if (exec)
            {
                exec();
                commandQueue.push(const_cast<CoreCommand *>(this));
            }
        }

        void CoreCommand::executeSave()
        {
            execute();
        }

        void CoreCommand::unExcute() const
        {
            if (undo)
            {
                undo();
                commandQueue.push(const_cast<CoreCommand *>(this));
            }
        }

        void CoreCommand::Success()
        {
            commandQueue.pop();
        }

        void CoreCommand::Error()
        {
            CommandManager::Instance()->removeCommand(commandQueue.front());
            commandQueue.pop();
        }
    }
}
