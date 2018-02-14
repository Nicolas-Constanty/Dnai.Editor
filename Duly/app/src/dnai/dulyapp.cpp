#include <QQuickWindow>
#include <QTimer>

#include "dnai/dulyapp.h"
#include "dnai/processmanager.h"
#include "dnai/controllers/consolecontroller.h"
#include "dnai/controllers/clientcontroller.h"
#include "dnai/commands/commandmanager.h"

namespace dnai
{
#pragma region Initialisation functions

    DulyApp *DulyApp::m_instance = nullptr;
	DulyApp::DulyApp(int& argc, char** argv) : QGuiApplication(argc, argv), m_settings(nullptr),
		m_currentCanvas(nullptr)
	{
		if (m_instance == nullptr)
			m_instance = this;
	}

	void DulyApp::initApp()
	{
		initProcessManager();
		installEventFilter(this);
		setupSettings();
		loadFonts();
		loadMainWindow();
	}

	void DulyApp::initProcessManager()
	{
#ifdef Q_OS_MAC
		m_processManager = new ProcessManager(QGuiApplication::applicationDirPath() + "/settings/conf/mac/bin_info.cfg");
#else
		m_processManager = new ProcessManager("./settings/conf/windows/bin_info.cfg");
#endif
		m_processManager->launch();
		ClientController::serverPort = m_processManager->getServerPort();
		ClientController::shared();
	}

	void DulyApp::setupSettings()
	{
		setOrganizationName("DNAI");
		setOrganizationDomain("DNAI.com");
		setApplicationName("DNAI");
	}

	void DulyApp::loadFonts()
	{
		QFontDatabase::addApplicationFont(":/resources/fonts/Font Awesome 5 Free-Solid-900.otf");
		QFontDatabase::addApplicationFont(":/resources/fonts/Font Awesome 5 Free-Regular-400.otf");
		QFontDatabase::addApplicationFont(":/resources/fonts/Font Awesome 5 Brands-Regular-400.otf");
		QFontDatabase::addApplicationFont(":/resources/fonts/Playball.ttf");
	}

	void DulyApp::loadMainWindow()
	{
		m_engine.load(QUrl(QLatin1String("qrc:/resources/main.qml")));
		if (m_engine.rootObjects().isEmpty())
			throw std::runtime_error("Fail to load main.qml");
	}

#pragma endregion 

#pragma region Application functions

	bool DulyApp::eventFilter(QObject* o, QEvent* event)
	{
		if (!event || event->type() != QEvent::KeyPress) return QGuiApplication::eventFilter(o, event);
		const auto e = dynamic_cast<QKeyEvent *>(event);
		if (e != nullptr)
		{
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
		}
		return QGuiApplication::eventFilter(o, event);
	}

	QObject* DulyApp::createQmlComponent(const QString &path)
	{
		QQmlComponent component(&m_engine, path);
		return component.create();
	}

#pragma endregion 

#pragma region Setter

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

	DulyApp* DulyApp::currentInstance()
	{
		return m_instance;
	}

#pragma endregion 

#pragma region Getter

	QQmlApplicationEngine const* DulyApp::engine() const
	{
		return &m_engine;
	}

	DulySettings* DulyApp::settings() const
	{
		return m_settings;
	}

	views::DulyCanvas* DulyApp::currentCanvas() const
	{
		return m_currentCanvas;
	}

	views::DulyCanvas* DulyApp::currentCanvasInstance()
	{
		return dynamic_cast<DulyApp *>(instance())->currentCanvas();
	}

	QObject* DulyApp::createQmlObject(const QString& path)
	{
		return DulyApp::currentInstance()->createQmlComponent(path);
	}

	QQmlEngine* DulyApp::getEngineInstance()
	{
		return const_cast<QQmlEngine *>(dynamic_cast<const QQmlEngine *>(DulyApp::currentInstance()->engine()));
	}

#pragma endregion 
}
