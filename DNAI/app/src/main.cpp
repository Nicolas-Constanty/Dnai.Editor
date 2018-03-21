#include <QGuiApplication>

#include "views.h"
#include "models.h"
#include "enums.h"

#include "dnai/app.h"
#include "dnai/manager.h"
#include "dnai/settings.h"
#include "dnai/project.h"
#include "dnai/editor.h"
#include "controllers.h"

#include "include/eventconsumer.h"
#include "dnai/entitiesfactory.h"
#include "dnai/viewshandler.h"
#include "dnai/enums/core/core.h"

#if defined(_WIN32) && defined(_MSC_VER)
#include "../../lib/WinToast/wintoastlib.h"
using namespace WinToastLib;
#endif

static QObject *manager_singleton_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return new dnai::Manager();
}

static QObject *editor_singleton_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
	Q_UNUSED(engine)
	Q_UNUSED(scriptEngine)
	
    return &dnai::Editor::instance();
}

static QObject *settings_singleton_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return new dnai::AppSettings();
}

static QObject *standardpath_singleton_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return new QCStandardPaths();
}

static void registerDNAI()
{
#define qmlRegisterDnai(type, name) qmlRegisterType<type>("DNAI", 1, 0, name)
    qmlRegisterSingletonType<dnai::Manager>("DNAI", 1, 0, "Manager", manager_singleton_provider);
	qmlRegisterSingletonType<dnai::Editor>("DNAI", 1, 0, "Editor", editor_singleton_provider);
    qmlRegisterSingletonType<dnai::AppSettings>("DNAI", 1, 0, "AppSettings", settings_singleton_provider);
    qmlRegisterSingletonType<QCStandardPaths>("DNAI", 1, 0, "StandardPath", standardpath_singleton_provider);
    qmlRegisterDnai(dnai::Session, "Session");
    qmlRegisterDnai(dnai::ViewsHandler, "ViewsHandler");
    qmlRegisterDnai(dnai::Project, "Project");
	qmlRegisterDnai(dnai::Solution, "Solution");
}

static void registerEnums()
{
#define qmlRegisterEnums(type, name) qmlRegisterType<type>("DNAI.Enums", 1, 0, name)
    qmlRegisterEnums(dnai::enums::IoTypeRessouce, "IOType");
    qmlRegisterEnums(dnai::enums::FlowTypeRessouce, "FlowType");
    qmlRegisterEnums(dnai::enums::DeclarationTypeRessouce, "DeclarationType");
    qmlRegisterEnums(dnai::enums::QInstructionID, "InstructionID");
    qmlRegisterUncreatableMetaObject(
      dnai::enums::core::staticMetaObject, // static meta object
      "DNAI.Enums",                // import statement (can be any string)
      1, 0,                          // major and minor version of the import
      "Core",                 // name in QML (does not have to match C++ name)
      "Error: only enums"            // error in case someone tries to create a MyNamespace object
    );
}

class conststr {
	const char* p;
	std::size_t sz;
public:
	template<std::size_t N>
	constexpr conststr(const char(&a)[N]) : p(a), sz(N - 1) {}

	// constexpr functions signal errors by throwing exceptions
	// in C++11, they must do so from the conditional operator ?:
	constexpr char operator[](std::size_t n) const
	{
		return n < sz ? p[n] : throw std::out_of_range("");
	}

	constexpr const char *raw() const
	{
		return p;
	}
};

struct RegisterInfo
{
    constexpr RegisterInfo(conststr ns, int version, int subversion)
		: ns(ns),
		  version(version),
		  subversion(subversion)
	{
	}

	conststr ns;
	const int version;
	const int subversion;
};

static void registerViews()
{
#define qmlRegisterViews(type, name) qmlRegisterType<type>("DNAI.Views", 1, 0, name)
    // QML Views
    qmlRegisterViews(dnai::views::CanvasNode, "CanvasNode");
//    qmlRegisterType<dnai::views::DeclarationCanvas>("DNAI.Views", 1, 0, "DeclarationCanvas");
    qmlRegisterViews(dnai::views::Console, "Console");
    qmlRegisterViews(dnai::views::ContextView, "ContextView");
    qmlRegisterViews(dnai::views::DeclarationView, "DeclarationViewModel");
    qmlRegisterViews(dnai::views::InstructionView, "InstructionViewModel");
    qmlRegisterViews(dnai::views::Layout, "LayoutView");
    qmlRegisterViews(dnai::views::AppView, "AppView");
    // OpenGL Geometries
    qmlRegisterViews(dnai::views::BezierCurve, "BezierCurve");
    qmlRegisterViews(dnai::views::Line, "Line");
    qmlRegisterViews(dnai::views::RoundedRectangle, "RoundedRectangle");
    qmlRegisterViews(dnai::views::GenericNode, "GenericNode");
    qmlRegisterViews(dnai::views::Input, "Input");
    qmlRegisterViews(dnai::views::Output, "Output");
    qmlRegisterViews(dnai::views::Flow, "Flow");
    qmlRegisterViews(dnai::views::ViewElement, "ViewElement");
    qmlRegisterViews(dnai::views::ViewZone, "ViewZoneBack");
    qmlRegisterViews(dnai::views::EditorView, "EditorView");
}



static void registerModels()
{
#define qmlRegisterModels(type, name) qmlRegisterType<type>("DNAI.Models", 1, 0, name)
    qmlRegisterModels(dnai::models::SettingsModel, "SettingsModel");
    qmlRegisterModels(dnai::models::QCanvas, "QCanvas");
    qmlRegisterModels(dnai::models::QGrid, "QGrid");
    qmlRegisterModels(dnai::models::QBorder, "QBorder");
    qmlRegisterModels(dnai::models::QNode, "QNode");
    qmlRegisterModels(dnai::models::QNodes, "QNodes");
    qmlRegisterModels(dnai::models::QDeclaration, "QDeclaration");
    qmlRegisterModels(dnai::models::QDeclarationView, "QDeclarationView");
    qmlRegisterModels(dnai::models::QTextSettings, "QTextSettings");
    qmlRegisterModels(dnai::models::QFontSettings, "QFontSettings");
    qmlRegisterModels(dnai::models::MenuSettings, "MenuSettings");
    qmlRegisterModels(dnai::models::QBackground, "QBackground");
//    qmlRegisterType<dnai::models::TreeModel>("DNAI.Models", 1, 0, "TreeModel");
//    qmlRegisterType<dnai::models::TreeItem>("DNAI.Models", 1, 0, "TreeItem");
//    qmlRegisterType<dnai::models::NameSpaceBarItem>("DNAI.Models", 1, 0, "NameSpaceBarItem");
//    qmlRegisterType<dnai::models::NameSpaceBarModel>("DNAI.Models", 1, 0, "NameSpaceBarModel");
    qmlRegisterModels(dnai::models::User, "User");
//    qmlRegisterType<dnai::models::DeclarationModel>("DNAI.Models", 1, 0, "DeclarationModel");
//    qmlRegisterType<dnai::models::Declaration>("DNAI.Models", 1, 0, "Declaration");
    qmlRegisterModels(dnai::models::BasicNodeModel, "BasicNodeModel");
    qmlRegisterModels(dnai::models::ListNode, "ListNode");
    qmlRegisterModels(dnai::models::Entity, "Entity");
    qmlRegisterModels(dnai::models::Column, "Column");
    qmlRegisterModels(dnai::models::EntityTree, "EntityTree");
//    qmlRegisterType<dnai::models::Property>("DNAI.Models", 1, 0, "Property");
//    qmlRegisterType<dnai::models::EntityList>("DNAI.Models", 1, 0, "EntityList");
}

static void registerConnection() {
    qmlRegisterType<EventConsumer>("DNAI.Communication.EventConsumer", 1, 0, "EventConsumer");
}

static void registerQml()
{
    registerEnums();
    registerModels();
    registerViews();
    registerConnection();
}

static void registerCustomTypes()
{
    qRegisterMetaTypeStreamOperators<dnai::api::User>("User");
}

int main(int argc, char *argv[])
{
    registerQml();
    registerCustomTypes();

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    dnai::App app(argc, argv);
#if defined(_WIN32) && defined(_MSC_VER)
    WinToast::instance()->setAppName(L"DNAI");
    WinToast::instance()->setAppUserModelId(
                WinToast::configureAUMI(L"SaltyStudio", L"DNAI", L"DNAI.app", L"20161006"));
    if (!WinToast::instance()->initialize()) {
        qDebug() << "Error, your system in not compatible!";
    }
#endif
    registerDNAI();
    app.load();
    return dnai::App::exec();
}


//    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
//    if (engine.rootObjects().isEmpty())
//        return -1;

    // DEBUT CODE POUR LA COMMUNICATION CLIENT SERVER

//    ClientCommunication com(QHostAddress::LocalHost, 7777, "DNAI GUI");
//    com.start();

//    TestConnection test(*com);

//    com->registerEvent("POPOLE", 4, std::bind(&TestConnection::onReceiveEventPopole, &test, std::placeholders::_1, std::placeholders::_2));

//    QTimer *timer = new QTimer();
//      QObject::connect(timer, SIGNAL(timeout()), &test, SLOT(update()));
//      timer->start(1000);


  /*  QTimer *timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), &test, SLOT(update()));
    timer->start(1000);
    QTimer *timer2 = new QTimer();
    QObject::connect(timer2, SIGNAL(timeout()), &test, SLOT(updateTITI()));
    timer2->start(3000);
    QTimer *timer3 = new QTimer();
    QObject::connect(timer3, SIGNAL(timeout()), &test, SLOT(updateTOTO()));
    timer3->start(5000);*/

    // FIN CODE COMMUNICATION SERVER
