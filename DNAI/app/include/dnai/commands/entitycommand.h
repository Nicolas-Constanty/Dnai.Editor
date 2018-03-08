#ifndef ENTITYCOMMAND_H
#define ENTITYCOMMAND_H

#include "command.h"

namespace dnai
{
	namespace commands
	{
		class EntityCommand : public Command
		{
		public:
			EntityCommand();

			void execute() const override;
			void unExcute() const override;
			void executeSave() override;
			~EntityCommand() override;
		};
	}
}

#endif //ENTITYCOMMAND_H