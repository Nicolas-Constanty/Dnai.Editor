#ifndef DNAI_COMMANDS_GENERICCOMMAND_H
#define DNAI_COMMANDS_GENERICCOMMAND_H

#include <functional>
#include "command.h"
#include "dnai/interfaces/ieditormodel.h"

namespace dnai
{
	namespace commands
	{
		template<class ...Args>
		class GenericCommand : public Command
		{
			GenericCommand(
				interfaces::IEditorModel *model,
				std::function<void(interfaces::IEditorModel*)> dofunc,
				std::function<void(interfaces::IEditorModel*)> undo, const QString &name, const bool save = false)
				: Command(name, save), m_model(model), m_dofunc(std::move(dofunc)), m_undo(std::move(undo))
			{}
		protected:
			void execute() const override
			{
				m_dofunc(m_model);
			}
			void executeSave() override
			{
				execute();
			}
			void unExcute() const override
			{
				m_undo(m_model);
			}
			QString infos() const override { return ""; }
			bool isSave() const override { return true; }

		private:
			interfaces::IEditorModel * m_model;
			std::function<void(interfaces::IEditorModel*)> m_dofunc;
			std::function<void(interfaces::IEditorModel*)> m_undo;
		};
	}
}

#endif //DNAI_COMMANDS_GENERICCOMMAND_H