#include <QKeyEvent>
#include "dulyapp.h"
#include "commands/commandmanager.h"

namespace duly_gui {
    DulyApp::DulyApp(int argc, char *argv[]) : QGuiApplication(argc, argv)
    {
        installEventFilter(this);
    }

    bool DulyApp::eventFilter(QObject *object, QEvent *event)
    {
        if (!event->KeyPress) return false;
		QKeyEvent *e = static_cast<QKeyEvent *>(event);
		if (e->matches(QKeySequence::Undo))
        {
			commands::CommandManager::Instance()->undo(1);
            return true;
		}
        if (e->matches(QKeySequence::Redo))
        {
            commands::CommandManager::Instance()->redo(1);
            return true;
        }
        return false;
    }
}


