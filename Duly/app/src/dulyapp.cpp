#include "dulyapp.h"
#include "commands/commandmanager.h"

namespace duly_gui {
    DulyApp::DulyApp(int & argc, char **argv) : QGuiApplication(argc, argv)
    {
        installEventFilter(this);
		m_currentCanvas = nullptr;
        QFontDatabase::addApplicationFont(":/resources/fonts/Font Awesome 5 Free-Solid-900.otf");
        QFontDatabase::addApplicationFont(":/resources/fonts/Font Awesome 5 Free-Regular-400.otf");
        QFontDatabase::addApplicationFont(":/resources/fonts/Font Awesome 5 Brands-Regular-400.otf");
        QFontDatabase::addApplicationFont(":/resources/fonts/Playball.ttf");
    }

	void DulyApp::registerEngine(QQmlApplicationEngine* engine)
	{
		m_engine = engine;
	}

	views::DulyCanvas *DulyApp::currentCanvasInstance()
    {
		return static_cast<DulyApp *>(DulyApp::instance())->currentCanvas();
    }

    bool DulyApp::eventFilter(QObject *o, QEvent *event)
    {
        if (!event || event->type() != QEvent::KeyPress) return QGuiApplication::eventFilter(o, event);
	    const auto e = static_cast<QKeyEvent *>(event);
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

	void DulyApp::registerSettings(DulySettings* dulySettings)
	{
		m_settings = dulySettings;
	}

	void DulyApp::registerCanvas(views::DulyCanvas* c)
	{
		if (!m_canvases.contains(c))
		{
			m_canvases.append(c);
			if (m_currentCanvas == nullptr)
				m_currentCanvas = c;
		}
	}

	void DulyApp::setCurrentCanvas(views::DulyCanvas* c)
	{
		if (!m_canvases.contains(c))
		{
			qDebug() << c << "Doesn't exist call registerCanvas() before";
			return;
		}
		m_currentCanvas = c;
	}

	void DulyApp::initApp()
	{
		setOrganizationName("DNAI");
		setOrganizationDomain("DNAI.com");
		setApplicationName("DNAI");
	}

//    void DulyApp::setCurrentPath(const QString &path) const
//    {
//        m_currentPath = path;
//    }
}
