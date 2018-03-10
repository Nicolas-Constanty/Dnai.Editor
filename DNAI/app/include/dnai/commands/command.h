#ifndef COMMAND_H
#define COMMAND_H
#include <QInputEvent>

#include "dnai/interfaces/icommand.h"

namespace dnai
{
	namespace commands
    {
        class Command : public QEvent, public interfaces::ICommand
		{
            static const QEvent::Type CommandEvent;
		public:
			explicit Command(const QString &name, bool save = false);

			//Implementation of ICommand
        public:
			virtual void execute() const override;
			virtual void executeSave() override;
			virtual void unExcute() const override;
			virtual QString infos() const override;
			virtual bool isSave() const override;

	        /**
	         * \brief Get the command name
	         * \return const QString& 
	         */
	        const QString& name() const;

		protected:
			const QString m_name;
			const bool m_save;
		};
	}
}

#endif // COMMAND_H
