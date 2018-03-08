#ifndef GENERICCOMMAND_H
#define GENERICCOMMAND_H

#include <functional>
#include "command.h"

namespace dnai
{
	namespace commands
	{
		template <class T>
		class LambdaCommand : public Command
		{
			static_assert(std::is_bind_expression<T>::value || std::is_function<T>::value , "T can be only a binding or function type");
		public:
			LambdaCommand(const T dof, const QString &name, bool save) : Command(name, save)
			{
				m_do = dof;
			}
			LambdaCommand(const T dof, const T unf, const QString &name, bool save) : Command(name, save)
			{
				m_do = dof;
				m_undo = unf;
			}

			void execute() const override
			{
				m_do();
			}

			void unExcute() const override
			{
				if (m_undo)
					m_undo();
			}

			void executeSave() override
			{
				execute();
			}

			~LambdaCommand() override
			{
			}

		private:
			T m_do;
			T m_undo;
		};
	}
}

#endif