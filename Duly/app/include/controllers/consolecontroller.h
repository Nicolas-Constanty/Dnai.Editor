#ifndef CONSOLECONTROLLER_H
#define CONSOLECONTROLLER_H
#include <QObject>
#include "views/console.h"
#include <QQuickItem>

namespace duly_gui
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
