#include <QQuickWindow>
#include <QTimer>

#include "dnai/app.h"
#include "dnai/processmanager.h"
#include "dnai/controllers/consolecontroller.h"
#include "dnai/controllers/clientcontroller.h"
#include "dnai/commands/commandmanager.h"
#include "api.h"
#include "http.h"

namespace dnai
{
#pragma region Initialisation functions

    App *App::m_instance = nullptr;
    App::App(int& argc, char** argv) : QGuiApplication(argc, argv)
	, m_settings(nullptr)
	, m_processManager(nullptr)
	, m_appView(nullptr)
	, m_nodeModel(nullptr)
	{
		if (m_instance == nullptr)
			m_instance = this;
	}

    App::~App() {
		if (m_settings)
			delete m_settings;
		if (m_processManager)
			delete m_processManager;
		if (m_appView)
			delete m_appView;
		if (m_nodeModel)
			delete m_nodeModel;
    }

    void App::initApp()
	{
		
	}

    void App::initProcessManager()
	{
        qDebug() << "YOLO";
#ifdef Q_OS_MAC
		m_processManager = new ProcessManager(QGuiApplication::applicationDirPath() + "/settings/conf/mac/bin_info.cfg");
#else
		m_processManager = new ProcessManager("./settings/conf/windows/bin_info.cfg");
#endif
		m_processManager->launch();
        controllers::ClientController::serverPort = m_processManager->getServerPort();
        controllers::ClientController::shared();
	}

    void App::setupSettings()
	{
		setOrganizationName("DNAI");
		setOrganizationDomain("DNAI.com");
		setApplicationName("DNAI");
	}

	void App::initAppView()
	{
		m_appView = new views::AppView();
		m_nodeModel = new models::BasicNodeModel();
	}

    std::queue<std::function<void()>> App::init()
	{
		std::queue<std::function<void()>> initFuncs;
        initFuncs.push(std::bind(&App::initProcessManager, this));
        initFuncs.push(std::bind(&App::installEventFilter, this, this));
        initFuncs.push(&App::setupSettings);
        initFuncs.push(&App::loadFonts);
		initFuncs.push(std::bind(&App::initAppView, this));
		initFuncs.push(std::bind(&App::loadMainWindow, this));
		initFuncs.push(std::bind(&dnai::http::Service::Init, dnai::api::http_config));
		return initFuncs;
	}

	void App::loadFonts()
	{
		QFontDatabase::addApplicationFont(":/resources/fonts/Font Awesome 5 Free-Solid-900.otf");
		QFontDatabase::addApplicationFont(":/resources/fonts/Font Awesome 5 Free-Regular-400.otf");
		QFontDatabase::addApplicationFont(":/resources/fonts/Font Awesome 5 Brands-Regular-400.otf");
		QFontDatabase::addApplicationFont(":/resources/fonts/Playball.ttf");
	}

    void App::loadMainWindow()
	{
		m_engine.load(QUrl(QLatin1String("qrc:/resources/main.qml")));
		if (m_engine.rootObjects().isEmpty())
			throw std::runtime_error("Fail to load main.qml");
	}

#pragma endregion 

#pragma region Application functions

    bool App::eventFilter(QObject* o, QEvent* event)
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

	models::BasicNodeModel* App::basicNodesModel() const
	{
		return m_nodeModel;
	}

	QObject* App::createQmlComponent(const QString &path)
	{
		QQmlComponent component(&m_engine, path);
        while (!component.isReady());
        return component.create();
	}

#pragma endregion 

#pragma region Setter

    void App::registerSettings(AppSettings* appSettings)
	{
        m_settings = appSettings;
	}

    App* App::currentInstance()
	{
		return m_instance;
	}

#pragma endregion 

#pragma region Getter

    QQmlApplicationEngine const* App::engine() const
	{
		return &m_engine;
	}

    AppSettings* App::settings() const
	{
		return m_settings;
	}

    QObject* App::createQmlObject(const QString& path)
	{
        return App::currentInstance()->createQmlComponent(path);
	}

    QQmlEngine* App::getEngineInstance()
	{
        return const_cast<QQmlEngine *>(dynamic_cast<const QQmlEngine *>(App::currentInstance()->engine()));
	}

    views::InstructionView* App::instructionView()
	{
		return dynamic_cast<views::InstructionView*>(currentInstance()->appView()->layout()->contextView());
	}

    views::AppView* App::appView() const
	{
		return m_appView;
	}

#pragma endregion 
}
