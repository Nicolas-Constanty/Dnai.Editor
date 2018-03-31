#include "dnai/commands/corecommand.h"

namespace dnai
{
    namespace commands
    {
        CoreCommand::CoreCommand(QString const &name, bool save, const Event &exec, const Event &undo) :
            Command(name, save),
            exec(exec),
            undo(undo)
        {

        }

        void CoreCommand::execute() const
        {
            exec();
        }

        void CoreCommand::executeSave()
        {
            execute();
        }

        void CoreCommand::unExcute() const
        {
            undo();
        }
    }
}
