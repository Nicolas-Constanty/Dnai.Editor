#include <QQuickWindow>
#include <QTimer>

#include "dnai/dulyapp.h"
#include "dnai/processmanager.h"
#include "dnai/controllers/consolecontroller.h"
#include "dnai/controllers/clientcontroller.h"
#include "dnai/commands/commandmanager.h"

namespace dnai {
DulyApp::DulyApp(int & argc, char **argv) : QGuiApplication(argc, argv)
{
   // QProcess *process = new QProcess(this);
   // QString file = QDir::homePath() + "/SplashScreen.exe";
   // process->start(file);
}

void DulyApp::registerEngine(QQmlApplicationEngine* engine)
{
    m_engine = engine;
}

void DulyApp::loadFonts()
{
    QFontDatabase::addApplicationFont(":/resources/fonts/Font Awesome 5 Free-Solid-900.otf");
    QFontDatabase::addApplicationFont(":/resources/fonts/Font Awesome 5 Free-Regular-400.otf");
    QFontDatabase::addApplicationFont(":/resources/fonts/Font Awesome 5 Brands-Regular-400.otf");
    QFontDatabase::addApplicationFont(":/resources/fonts/Playball.ttf");
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
    initProcessManager();
    installEventFilter(this);
    m_currentCanvas = nullptr;
    setupSettings();
    loadFonts();
    loadMainWindow();
//    QTimer::singleShot(10000, this, SLOT(loadMainWindow()));
}

void DulyApp::loadMainWindow()
{
    m_engine->load(QUrl(QLatin1String("qrc:/resources/main.qml")));
    if (m_engine->rootObjects().isEmpty())
        throw std::runtime_error("Fail to load main.qml");
}

void DulyApp::initProcessManager()
{
#ifdef Q_OS_MAC
    ProcessManager *processManager = new ProcessManager(QGuiApplication::applicationDirPath() + "/settings/conf/mac/bin_info.cfg");
#else
    ProcessManager *processManager = new ProcessManager("./settings/conf/windows/bin_info.cfg");
#endif
    processManager->launch();
    ClientController::serverPort = processManager->getServerPort();
    ClientController::shared();
}

void DulyApp::setupSettings()
{
    setOrganizationName("DNAI");
    setOrganizationDomain("DNAI.com");
    setApplicationName("DNAI");
}
}
