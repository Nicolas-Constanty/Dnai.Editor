#ifndef CONSOLECONTROLLER_H
#define CONSOLECONTROLLER_H

#include <QObject>
#include <QQuickItem>

#include "dnai/views/console.h"
namespace dnai
{
	namespace controllers
	{
        class ConsoleController
        {
		public:
            explicit ConsoleController();
			void writeLine(const QString& text) const;

            void setConsole(views::Console *c);
            views::Console *view() const { return m_view; }

		private:
            views::Console *m_view;
		};
	}
}

#endif // CONSOLECONTROLLER_H
