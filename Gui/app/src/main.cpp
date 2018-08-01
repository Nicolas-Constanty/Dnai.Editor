#include <QGuiApplication>
#include <QLoggingCategory>

#include "dnai.h"
#include "dnai/app.h"
#include "dnai/editor.h"
#include "dnai/project.h"
#include "dnai/core/handlermanager.h"

#if defined(_WIN32) && defined(_MSC_VER)
#include "../../lib/lwintoast/wintoastlib.h"
using namespace WinToastLib;
#include <QSslSocket>
#include <tchar.h>
#include <signal.h>
#else
#include <signal.h>
#endif

static QObject *editor_singleton_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return &dnai::Editor::instance();
}

static QObject *standardpath_singleton_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return new QCStandardPaths();
}

static QObject *core_controller_singleton_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return &dnai::gcore::HandlerManager::Instance();
}

static void registerDNAI()
{
#define qmlRegisterDnai(type, name) qmlRegisterType<type>("DNAI", 1, 0, name);
    qmlRegisterSingletonType<dnai::Editor>("DNAI", 1, 0, "Editor", editor_singleton_provider);
    qmlRegisterSingletonType<QCStandardPaths>("DNAI", 1, 0, "StandardPath", standardpath_singleton_provider);
    qmlRegisterDnai(dnai::Session, "Session");
    qmlRegisterDnai(dnai::Project, "Project");
    qmlRegisterDnai(dnai::Solution, "Solution");
    qmlRegisterDnai(dnai::models::gui::EntityList, "EntityList");
    qmlRegisterDnai(dnai::models::ContextMenuModel, "ContextMenuModel");
    qmlRegisterDnai(dnai::models::ml::Dataset, "Dataset");
    qmlRegisterDnai(dnai::utils::IterableQQmlPropertyMap, "IterableQQmlPropertyMap");
}

static void registerEnums()
{

#define qmlRegisterEnums(type, name) qmlRegisterType<type>("DNAI.Enums", 1, 0, name)
    qmlRegisterEnums(dnai::enums::IoTypeRessouce, "IOType");
    qmlRegisterEnums(dnai::enums::FlowTypeRessouce, "FlowType");
    qmlRegisterEnums(dnai::enums::DeclarationTypeRessouce, "DeclarationType");
    qmlRegisterEnums(dnai::enums::QInstructionID, "InstructionID");
    qmlRegisterUncreatableMetaObject(::core::staticMetaObject,
                                     "DNAI.Enums",
                                     1, 0,
                                     "CoreEnums",
                                     "Error: only enums");
    //    qmlRegisterEnums(dnai::enums::core, "CoreEnums");
    //qmlRegisterEnums(dnai::enums::core, "Core");
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
    qmlRegisterModels(dnai::models::User, "User");
    qmlRegisterModels(dnai::models::Entity, "Entity");
    qmlRegisterModels(dnai::models::Column, "Column");
    qmlRegisterModels(dnai::models::EntityTree, "EntityTree");
    qmlRegisterModels(dnai::models::gui::declarable::EnumType, "EnumType");
    qmlRegisterModels(dnai::models::gui::Instruction, "Instruction");
}

static void registerCore() {
    if (!qmlRegisterUncreatableType<dnai::gcore::ProjectHandler>("DNAI.Core", 1, 0, "ProjectHandler", "Use DNAI.Core.Controller.project")
            || !qmlRegisterUncreatableType<dnai::gcore::DeclaratorHandler>("DNAI.Core", 1, 0, "DeclaratorHandler", "Use DNAI.Core.Controller.declarator")
            || !qmlRegisterUncreatableType<dnai::gcore::VariableHandler>("DNAI.Core", 1, 0, "VariableHandler", "Use DNAI.Core.Controller.variable")
            || !qmlRegisterUncreatableType<dnai::gcore::EnumHandler>("DNAI.Core", 1, 0, "EnumerationHandler", "Use DNAI.Core.Controller.enumeration")
            || !qmlRegisterUncreatableType<dnai::gcore::FunctionHandler>("DNAI.Core", 1, 0, "FunctionHandler", "Use DNAI.Core.Controller.function")
            || !qmlRegisterUncreatableType<dnai::gcore::InstructionHandler>("DNAI.Core", 1, 0, "InstructionHandler", "Use DNAI.Core.Controller.function.instruction")
            //list handler
            || !qmlRegisterUncreatableType<dnai::gcore::ObjectHandler>("DNAI.Core", 1, 0, "ObjectHandler", "Use DNAI.Core.Controller.Class")
            || !qmlRegisterSingletonType<dnai::gcore::HandlerManager>("DNAI.Core", 1, 0, "Controller", core_controller_singleton_provider))
        qDebug() << "==main== Failed to register one core type";
}

static void registerQml()
{
    registerEnums();
    registerModels();
    registerViews();
    registerCore();
}

static void registerCustomTypes()
{
    qRegisterMetaTypeStreamOperators<dnai::api::User>("User");
}

void error_callBack(int signal) {
   dnai::App::currentInstance().close(signal);
   exit(signal);
}

int main(int argc, char *argv[])
{

    signal(SIGSEGV, error_callBack);
    signal(SIGABRT, error_callBack);
    signal(SIGINT, error_callBack);
    signal(SIGTERM, error_callBack);

    registerQml();
    registerCustomTypes();
    registerDNAI();

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    dnai::App app(argc, argv);


    dnai::Editor::instance().setAppName(argv[0]);

    return dnai::App::exec();
}
