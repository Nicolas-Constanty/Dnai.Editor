#include <QQuickWindow>
#include <QTimer>
#include <QDir>

#include "dnai/app.h"
#include "dnai/processmanager.h"
#include "dnai/controllers/consolecontroller.h"
#include "core.h"
#include "dnai/commands/commandmanager.h"
#include "api.h"
#include "http.h"
#include <QDirIterator>
#include <QQmlProperty>

#if defined(_WIN32) && defined(_MSC_VER)
#include "../../lib/WinToast/wintoastlib.h"
using namespace WinToastLib;
#endif
#if defined(Q_OS_MAC)
#include "../../lib/MACToast/toast.h"
#endif

namespace dnai
{
    App *App::m_instance = nullptr;
    App::App(int& argc, char** argv) : QGuiApplication(argc, argv)
	, m_settings(nullptr)
	, m_processManager(nullptr)
	, m_appView(nullptr)
	, m_nodeModel(nullptr)
	, m_editor(Editor::instance())
    , m_currentVersion()
    , m_currentVersionAPI()
	{
		if (m_instance == nullptr)
			m_instance = this;
	}

    App::~App() {
	    delete m_processManager;
	    delete m_appView;
	    delete m_nodeModel;
        qDebug() << "~" << "App";
    }

    void App::versionsUpdater() {
#ifdef Q_OS_MAC
        QString softwares("mac");
#else
        QString softwares("windows");
#endif
        m_currentVersion = DNAI_VERSION_RELEASE;
        m_currentVersionAPI = m_currentVersion;

        api::get_download_object(softwares, "installer").map([this](Response response) -> Response {
            if (response.body.contains("currentVersion")) {
                m_currentVersionAPI = response.body["currentVersion"].toString();
            }
            return response;
        },
        [this](Response response) -> Response {
            qDebug() << "ERROR";
            return response;
        });
    }

    void App::initProcessManager()
	{
#ifdef Q_OS_MAC
		m_processManager = new ProcessManager(QGuiApplication::applicationDirPath() + "/settings/conf/mac/bin_info.cfg");
#else
        m_processManager = new ProcessManager(QGuiApplication::applicationDirPath() + "/settings/conf/windows/bin_info.cfg");
#endif
		m_processManager->launch();
        core::connect(m_processManager->getServerPort()); //connect core client
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
        initFuncs.push(std::bind(&App::versionsUpdater, this));
		return initFuncs;
	}

	void App::loadFonts()
    {
        QDirIterator it(":/resources/fonts/", QDirIterator::Subdirectories);
        while (it.hasNext()) {
            if (it.fileInfo().isFile())
            {
                  QFontDatabase::addApplicationFont(it.filePath());
            }
           it.next();
		}
	}

    void App::loadMainWindow()
	{
		m_engine.load(QUrl(QLatin1String("qrc:/resources/main.qml")));
		if (m_engine.rootObjects().isEmpty())
			throw std::runtime_error("Fail to load main.qml");
	}

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

    models::BasicNodeModel *App::nodes() const
	{
		return m_nodeModel;
	}

    Editor &App::editor() const
	{
		return m_editor;
	}

	QObject* App::createQmlComponent(const QString &path)
	{
		QQmlComponent component(&m_engine, path);
        while (!component.isReady());
        return component.create();
	}

    void App::registerSettings(AppSettings* appSettings)
	{
        m_settings = appSettings;
	}

    App* App::currentInstance()
	{
		return m_instance;
	}

    QQmlApplicationEngine &App::engine()
	{
		return m_engine;
	}

    AppSettings &App::settings() const
	{
        return *m_settings;
	}

    Session  &App::session()
	{
        return m_session;
	}

	QObject* App::createQmlObject(const QString& path)
	{
        return App::currentInstance()->createQmlComponent(path);
	}

    QQmlEngine *App::getEngineInstance()
	{
        return const_cast<QQmlEngine *>(dynamic_cast<const QQmlEngine *>(&App::currentInstance()->engine()));
	}

    views::InstructionView* App::instructionView()
	{
		return dynamic_cast<views::InstructionView*>(currentInstance()->appView().layout()->contextView());
	}

    views::AppView &App::appView() const
	{
		return *m_appView;
	}
#if defined(_WIN32) && defined(_MSC_VER)
  class CustomHandler : public IWinToastHandler {
  public:
      void toastActivated() const {
          std::wcout << L"The user clicked in this toast" << std::endl;
      }

      void toastActivated(int actionIndex) const {
          std::wcout << L"The user clicked on button #" << actionIndex << L" in this toast" << std::endl;
      }

      void toastFailed() const {
          std::wcout << L"Error showing current toast" << std::endl;
      }
      void toastDismissed(WinToastDismissalReason state) const {
          switch (state) {
          case UserCanceled:
              std::wcout << L"The user dismissed this toast" << std::endl;
              break;
          case ApplicationHidden:
              std::wcout <<  L"The application hid the toast using ToastNotifier.hide()" << std::endl;
              break;
          case TimedOut:
              std::wcout << L"The toast has timed out" << std::endl;
              break;
          default:
              std::wcout << L"Toast not activated" << std::endl;
              break;
          }
      }
  };
#endif
  void App::onBuildStart()
  {
#if defined(_WIN32) && defined(_MSC_VER)
     WinToastTemplate templ = WinToastTemplate(WinToastTemplate::ImageAndText04);
     templ.setTextField(QString("Build Start at :").toStdWString(), WinToastTemplate::FirstLine);
     QDateTime dateTime = dateTime.currentDateTime();
     QString dateTimeString = dateTime.toString("yyyy-MM-dd hh:mm:ss");
     templ.setTextField(dateTimeString.toStdWString(), WinToastTemplate::SecondLine);
     templ.setTextField(QString("by Nicolas C").toStdWString(), WinToastTemplate::ThirdLine);
     templ.setExpiration(10000);

     if (WinToast::instance()->showToast(templ, new CustomHandler()) < 0) {
         qDebug() << "Error", "Could not launch your toast notification!";
     }
#endif
#if defined(Q_OS_MAC)
    Toast macToast;
    macToast.show("DNAI", "Build has start !");
#endif
  }

  bool App::isMac()
  {
#if defined(Q_OS_MAC)
    return true;
#else
      return false;
#endif
  }
}
