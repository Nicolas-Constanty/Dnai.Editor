#ifndef ENTITYCOMMAND_H
#define ENTITYCOMMAND_H

#include "command.h"

namespace dnai
{
	namespace commands
	{
        class CoreCommand : public Command
		{
		public:
            CoreCommand(std::function<void()> exec, std::function<void()> reverse);

			void execute() const override;
			void unExcute() const override;
			void executeSave() override;
			~CoreCommand() override;

        private:
			const std::function<void()> m_exec;
			std::function<void()> m_reverse;
		};
	}
}

#endif //ENTITYCOMMAND_H
