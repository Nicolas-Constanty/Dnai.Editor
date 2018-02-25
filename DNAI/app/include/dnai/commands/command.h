#ifndef COMMAND_H
#define COMMAND_H
#include <QInputEvent>

#include "icommand.h"

namespace dnai
{
	namespace commands
    {
		class Command : public QEvent, public ICommand
		{
		public:
			explicit Command(const QString &name, bool save = false);

			virtual void execute() const override;

			virtual void unExcute() const override;

			virtual void executeSave() override;

			virtual bool isSave() const override;

			const QString &name() const { return m_name; }

            QString infos() const override;

		protected:
			const QString m_name;
			const bool m_save;
		};
	}
}

#endif // COMMAND_H
