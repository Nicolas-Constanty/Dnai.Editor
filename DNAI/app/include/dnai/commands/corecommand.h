#ifndef ENTITYCOMMAND_H
#define ENTITYCOMMAND_H

#include <memory>

#include "dnai/enums/core/core.h"
#include "command.h"
#include "dnai/controllers/clientcontroller.h"

namespace dnai
{
	namespace commands
    {
        template <typename DoData, typename UndoData>
        class CoreCommand : public Command
        {
		public:
            CoreCommand(DoData *doData, UndoData *undoData, bool save) :
                Command("CoreCommand", save),
                doData(doData),
                undoData(undoData)
            {

            }

            virtual ~CoreCommand() = default;

        public:
            void execute() const override
            {
                dnai::controllers::ClientController::shared().sendCommand(*doData);
            }

            void unExcute() const override
            {
                dnai::controllers::ClientController::shared().sendCommand(*undoData);
            }

            void executeSave() override
            {
                execute();
            }

        private:
            std::unique_ptr<DoData> doData;
            std::unique_ptr<UndoData> undoData;
		};
	}
}

#endif //ENTITYCOMMAND_H
