#include <QGuiApplication>

#include "dnai.h"
#include "dnai/editor.h"
#include "dnai/project.h"

#if defined(_WIN32) && defined(_MSC_VER)
#include "../../lib/WinToast/wintoastlib.h"
using namespace WinToastLib;
#endif

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
#define qmlRegisterDnai(type, name) qmlRegisterType<type>("DNAI", 1, 0, name);
	qmlRegisterSingletonType<dnai::Editor>("DNAI", 1, 0, "Editor", editor_singleton_provider);
    qmlRegisterSingletonType<dnai::AppSettings>("DNAI", 1, 0, "AppSettings", settings_singleton_provider);
    qmlRegisterSingletonType<QCStandardPaths>("DNAI", 1, 0, "StandardPath", standardpath_singleton_provider);
    qmlRegisterDnai(dnai::Session, "Session");
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
    qmlRegisterEnums(dnai::enums::core, "Core");
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
    qmlRegisterModels(dnai::models::User, "User");
    qmlRegisterModels(dnai::models::BasicNodeModel, "BasicNodeModel");
    qmlRegisterModels(dnai::models::ListNode, "ListNode");
    qmlRegisterModels(dnai::models::Entity, "Entity");
    qmlRegisterModels(dnai::models::Column, "Column");
    qmlRegisterModels(dnai::models::EntityTree, "EntityTree");
}

static void registerConnection() {
    //qmlRegisterType<EventConsumer>("DNAI.Communication.EventConsumer", 1, 0, "EventConsumer");
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
