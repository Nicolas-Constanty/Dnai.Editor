#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <functional>

#include "api.h"
#include "http.h"
#include "views.h"
#include "models.h"
#include "qmlresources.h"

#include "dnai/app.h"
#include "dnai/manager.h"
#include "dnai/settings.h"

#include "include/eventconsumer.h"

static QObject *manager_singleton_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return new dnai::Manager();
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
    qmlRegisterSingletonType<dnai::Manager>("DNAI", 1, 0, "Manager", manager_singleton_provider);
    qmlRegisterSingletonType<dnai::AppSettings>("DNAI", 1, 0, "AppSettings", settings_singleton_provider);
    qmlRegisterSingletonType<QCStandardPaths>("DNAI", 1, 0, "StandardPath", standardpath_singleton_provider);
}

static void registerEnums()
{
    qmlRegisterType<dnai::qmlresources::IoTypeRessouce>("DNAI.Enums", 1, 0, "IOType");
    qmlRegisterType<dnai::qmlresources::FlowTypeRessouce>("DNAI.Enums", 1, 0, "FlowType");
    qmlRegisterType<dnai::qmlresources::DeclarationTypeRessouce>("DNAI.Enums", 1, 0, "DeclarationType");
    qmlRegisterType<dnai::qmlresources::QInstructionID>("DNAI.Enums", 1, 0, "InstructionID");
}

static void registerViews()
{
    // QML Views
    qmlRegisterType<dnai::views::CanvasNode>("DNAI.Views", 1, 0, "CanvasNode");
    qmlRegisterType<dnai::views::CanvasNode>("DNAI.Views", 1, 0, "CanvasNode");
    qmlRegisterType<dnai::views::DeclarationCanvas>("DNAI.Views", 1, 0, "DeclarationCanvas");
    qmlRegisterType<dnai::views::Console>("DNAI.Views", 1, 0, "Console");
    qmlRegisterType<dnai::views::DeclarationView>("DNAI.Views", 1, 0, "DeclarationViewModel");
    qmlRegisterType<dnai::views::InstructionView>("DNAI.Views", 1, 0, "InstructionViewModel");
    qmlRegisterType<dnai::views::Layout>("DNAI.Views", 1, 0, "LayoutView");
    qmlRegisterType<dnai::views::AppView>("DNAI.Views", 1, 0, "AppView");
    // OpenGL Geometries
    qmlRegisterType<dnai::views::BezierCurve>("DNAI.Views", 1, 0, "BezierCurve");
    qmlRegisterType<dnai::views::Line>("DNAI.Views", 1, 0, "Line");
    qmlRegisterType<dnai::views::RoundedRectangle>("DNAI.Views", 1, 0, "RoundedRectangle");
    qmlRegisterType<dnai::views::GenericNode>("DNAI.Views", 1, 0, "GenericNode");
    qmlRegisterType<dnai::views::Input>("DNAI.Views", 1, 0, "Input");
    qmlRegisterType<dnai::views::Output>("DNAI.Views", 1, 0, "Output");
    qmlRegisterType<dnai::views::Flow>("DNAI.Views", 1, 0, "Flow");
}

static void registerModels()
{
    qmlRegisterType<dnai::models::SettingsModel>("DNAI.Models", 1, 0, "SettingsModel");
    qmlRegisterType<dnai::models::QCanvas>("DNAI.Models", 1, 0, "QCanvas");
    qmlRegisterType<dnai::models::QGrid>("DNAI.Models", 1, 0, "QGrid");
    qmlRegisterType<dnai::models::QBorder>("DNAI.Models", 1, 0, "QBorder");
    qmlRegisterType<dnai::models::QNode>("DNAI.Models", 1, 0, "QNode");
    qmlRegisterType<dnai::models::QNodes>("DNAI.Models", 1, 0, "QNodes");
    qmlRegisterType<dnai::models::QDeclaration>("DNAI.Models", 1, 0, "QDeclaration");
    qmlRegisterType<dnai::models::QDeclarationView>("DNAI.Models", 1, 0, "QDeclarationView");
    qmlRegisterType<dnai::models::QTextSettings>("DNAI.Models", 1, 0, "QTextSettings");
    qmlRegisterType<dnai::models::QFontSettings>("DNAI.Models", 1, 0, "QFontSettings");
    qmlRegisterType<dnai::models::MenuSettings>("DNAI.Models", 1, 0, "MenuSettings");
    qmlRegisterType<dnai::models::QBackground>("DNAI.Models", 1, 0, "QBackground");
    qmlRegisterType<dnai::models::TreeModel>("DNAI.Models", 1, 0, "TreeModel");
    qmlRegisterType<dnai::models::TreeItem>("DNAI.Models", 1, 0, "TreeItem");
    qmlRegisterType<dnai::models::NameSpaceBarItem>("DNAI.Models", 1, 0, "NameSpaceBarItem");
    qmlRegisterType<dnai::models::NameSpaceBarModel>("DNAI.Models", 1, 0, "NameSpaceBarModel");
    qmlRegisterType<dnai::models::User>("DNAI.Models", 1, 0, "User");
    qmlRegisterType<dnai::models::DeclarationModel>("DNAI.Models", 1, 0, "DeclarationModel");
    qmlRegisterType<dnai::models::Declaration>("DNAI.Models", 1, 0, "Declaration");
}

static void registerConnection() {
    qmlRegisterType<EventConsumer>("DNAI.Communication.EventConsumer", 1, 0, "EventConsumer");
}

static void registerQml()
{
    registerDNAI();
    registerEnums();
    registerModels();
    registerViews();
    registerConnection();
}

int main(int argc, char *argv[])
{
    registerQml();
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    dnai::App app(argc, argv);
    app.initApp();

    dnai::http::Service::Init(dnai::api::http_config);

    return app.exec();
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
