#include <QKeyEvent>
#include "dulyapp.h"
#include "commands/commandmanager.h"

namespace duly_gui {
    DulyApp::DulyApp(int & argc, char **argv) : QGuiApplication(argc, argv)
    {
        installEventFilter(this);
    }

    bool DulyApp::eventFilter(QObject *o, QEvent *event)
    {
        if (!event || event->type() != QEvent::KeyPress) return QGuiApplication::eventFilter(o, event);
		QKeyEvent *e = static_cast<QKeyEvent *>(event);
		if (e->matches(QKeySequence::Undo))
        {
			commands::CommandManager::Instance()->undo(1);
            return true;
		}
        else if (e->matches(QKeySequence::Redo))
        {
            commands::CommandManager::Instance()->redo(1);
            return true;
        }
        return QGuiApplication::eventFilter(o, event);
    }
}
