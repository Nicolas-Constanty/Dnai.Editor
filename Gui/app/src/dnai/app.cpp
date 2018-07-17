#include <QQuickWindow>
#include <QDirIterator>
#include <QFontDatabase>
#include <QDesktopServices>

#include "dnai/app.h"
#include "dnai/processmanager.h"
#include "dnai/controllers/consolecontroller.h"
#include "core.h"
#include "dnai/commands/commandmanager.h"
#include "api.h"
#include "http.h"

#if defined(_WIN32) && defined(_MSC_VER)
#include "../../lib/lwintoast/wintoastlib.h"
using namespace WinToastLib;
#endif
#if defined(Q_OS_MAC)
//#include "../../lib/MACToast/toast.h"
#endif

namespace dnai
{
    App *App::m_instance = nullptr;
    App::App(int& argc, char** argv) : QGuiApplication(argc, argv)
	, m_processManager(nullptr)
    , m_editor(Editor::instance())
	{
		if (m_instance == nullptr)
            m_instance = this;
        setupSettings();
        if (argc > 1)
            editor().setSolutionName(argv[1]);
        QString locale = QLocale::system().name();

        m_translator.load(QString("dnai_") + locale, applicationDirPath());
        qDebug() << "Translator " << QString("dnai_") + locale << QGuiApplication::installTranslator(&m_translator);
        QTimer::singleShot(300, this, &App::loadSplashScreen);
	}

    void App::loadSplashScreen()
    {
        m_engine.load(QUrl(QLatin1String("qrc:/resources/main.qml")));
        if (m_engine.rootObjects().isEmpty())
            throw std::runtime_error("Fail to load main.qml");
        QMetaObject::invokeMethod(m_engine.rootObjects().first(), "load");
    }

    App::~App() {
	    delete m_processManager;
        qDebug() << "~" << "App";
    }

    void App::versionsUpdater() {
#ifdef Q_OS_MAC
        const QString softwares("mac");
#else
	    const QString softwares("windows");
#endif
        setVersion(DNAI_VERSION_RELEASE);
        setAPIVersion(DNAI_VERSION_RELEASE);


        api::get_download_object(softwares, "installer").map([this](http::Response response) -> http::Response {
            if (response.body.contains("currentVersion")) {
                setAPIVersion(response.body["currentVersion"].toString());
            }
            qDebug() << "==App== DNAI release version:" << DNAI_VERSION_RELEASE;
            qDebug() << "==App== Editor version: " << Editor::instance().version();
            qDebug() << "==App== API version: " << m_currentVersionAPI;


            onNotifyVersionChanged();
            return response;
        },
        [this](http::Response response) -> http::Response {
            Editor::instance().notifyError("Could not check for update.");
       //     m_settings->setAPIVersion("0.0.30");
       //     onNotifyVersionChanged();

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
        setOrganizationName("SaltyStudio");
        setOrganizationDomain("dnai.io");
		setApplicationName("DNAI");
	}

	void App::initAppView()
	{
        QVariant value = Editor::instance().settings()->value(api::settings_key);
        api::setUser(value.value<api::User>());
        qDebug() << "==App== API id: " << api::getId();
	}

    std::queue<std::function<void()>> App::init()
	{
		std::queue<std::function<void()>> initFuncs;
        initFuncs.push(std::bind(&App::initProcessManager, this));
        initFuncs.push(std::bind(&App::installEventFilter, this, this));
//        initFuncs.push(&App::setupSettings);
        initFuncs.push(&App::loadFonts);
        initFuncs.push(std::bind(&App::initAppView, this));
        initFuncs.push(std::bind(&dnai::http::Service::Init, dnai::api::http_config));
		return initFuncs;
	}

    void App::afterInit()
    {}

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
        QMetaObject::invokeMethod(m_engine.rootObjects().first(), "load");
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

    ProcessManager *App::processManager() const
    {
        return m_processManager;
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

    App* App::currentInstance()
	{
		return m_instance;
	}

    QQmlApplicationEngine &App::engine()
	{
		return m_engine;
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

#if defined(_WIN32) && defined(_MSC_VER)
//  class CustomHandler : public IWinToastHandler {
//  public:
//      void toastActivated() const override
//      {
//          std::wcout << L"The user clicked in this toast" << std::endl;
//      }

//      void toastActivated(int actionIndex) const override
//      {
//          std::wcout << L"The user clicked on button #" << actionIndex << L" in this toast" << std::endl;
//      }

//      void toastFailed() const override
//      {
//          std::wcout << L"Error showing current toast" << std::endl;
//      }
//      void toastDismissed(WinToastDismissalReason state) const override
//      {
//          switch (state) {
//          case UserCanceled:
//              std::wcout << L"The user dismissed this toast" << std::endl;
//              break;
//          case ApplicationHidden:
//              std::wcout <<  L"The application hid the toast using ToastNotifier.hide()" << std::endl;
//              break;
//          case TimedOut:
//              std::wcout << L"The toast has timed out" << std::endl;
//              break;
//          default:
//              std::wcout << L"Toast not activated" << std::endl;
//              break;
//          }
//      }
//  };
#endif
  void App::onBuildStart()
  {
#if defined(_WIN32) && defined(_MSC_VER)
//     WinToastTemplate templ = WinToastTemplate(WinToastTemplate::ImageAndText04);
//     templ.setTextField(QString("Build Start at :").toStdWString(), WinToastTemplate::FirstLine);
//     QDateTime dateTime = dateTime.currentDateTime();
//     QString dateTimeString = dateTime.toString("yyyy-MM-dd hh:mm:ss");
//     templ.setTextField(dateTimeString.toStdWString(), WinToastTemplate::SecondLine);
//     templ.setTextField(QString("by Nicolas C").toStdWString(), WinToastTemplate::ThirdLine);
//     templ.setExpiration(10000);

//     if (WinToast::instance()->showToast(templ, new CustomHandler()) < 0) {
//         qDebug() << "Error", "Could not launch your toast notification!";
//     }
#endif
#if defined(Q_OS_MAC)
    //ToastMac macToast;
    //macToast.show("DNAI", "Build has start !");
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

  void App::setVersion(QString const &ver) {
      Editor::instance().setVersion(ver);
  }

  void App::setAPIVersion(QString const &ver) {
      m_currentVersionAPI = ver;
  }

  qreal App::getSettingNumber(const QString &path)
  {
      if (m_loadedNumbers.contains(path))
      {
          return m_loadedNumbers[path];
      }
      const auto s =  Editor::instance().settings()->value(path).toReal();
      m_loadedNumbers[path] = s;
      return m_loadedNumbers[path];
  }

  bool App::isNewVersionAvailable() const {
      QStringList currentVersionList = Editor::instance().version().split('.');
      QStringList currentVersionAPIList = m_currentVersionAPI.split('.');
      int i = 0;

      while (i < currentVersionAPIList.length() && i < currentVersionList.length()) {
          if (currentVersionAPIList[i].toInt() > currentVersionList[i].toInt()) {
              return true;
          }
          if ( currentVersionList[i].toInt() > currentVersionAPIList[i].toInt()) {
              break;
          }
          ++i;
      }
      return false;
  }

  void App::onNotifyVersionChanged() {
      if (isNewVersionAvailable()) {
          Editor::instance().notifyInformation("Switch to new version " + m_currentVersionAPI, [this]() {
              QDesktopServices::openUrl(QUrl("https://dnai.io/download/"));
             // App::currentInstance()->processManager()->launchUpdater(Editor::instance().version(), m_currentVersionAPI);
          });
          /*Editor::instance().notifyError("Switch to new version " + m_currentVersionAPI, [this]() {
              App::currentInstance()->processManager()->launchUpdater(Editor::instance().version(), m_currentVersionAPI);
          });
          Editor::instance().notifySuccess("Switch to new version " + m_currentVersionAPI, [this]() {
              App::currentInstance()->processManager()->launchUpdater(Editor::instance().version(), m_currentVersionAPI);
          });
          Editor::instance().notifyWarning("Switch to new version " + m_currentVersionAPI, [this]() {
              App::currentInstance()->processManager()->launchUpdater(Editor::instance().version(), m_currentVersionAPI);
          });*/
      }
  }
}
