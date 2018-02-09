#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <functional>

#include "views.h"
#include "model.h"
#include "http.h"
#include "api.h"
#include "qmlresources.h"

#include "dulyapp.h"
#include "manager.h"
#include "include/eventconsumer.h"
#include "dulysettings.h"

static QObject *manager_singleton_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return new duly_gui::Manager();
}

static QObject *settings_singleton_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return new duly_gui::DulySettings();
}

static QObject *standardpath_singleton_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return new QCStandardPaths();
}

static void registerCustomConnection() {
    qmlRegisterType<EventConsumer>("Communication.EventConsumer", 1, 0, "EventConsumer");
}

static void registerCustomViews()
{
    qmlRegisterType<duly_gui::views::DulyCanvas>("CustomViews", 1, 0, "DulyCanvas");
    qmlRegisterType<duly_gui::views::GenericNode>("CustomViews", 1, 0, "GenericNode");
    qmlRegisterType<duly_gui::views::Input>("CustomViews", 1, 0, "Input");
    qmlRegisterType<duly_gui::views::Output>("CustomViews", 1, 0, "Output");
    qmlRegisterType<duly_gui::views::Flow>("CustomViews", 1, 0, "Flow");
    qmlRegisterType<duly_gui::views::DulyCanvas>("CustomViews", 1, 0, "DulyCanvas");
    qmlRegisterType<duly_gui::views::DeclarationCanvas>("CustomViews", 1, 0, "DeclarationCanvas");

}
static void registerCustomGeometry()
{
    qmlRegisterType<duly_gui::views::BezierCurve>("CustomGeometry", 1, 0, "BezierCurve");
    qmlRegisterType<duly_gui::views::Line>("CustomGeometry", 1, 0, "Line");
    qmlRegisterType<duly_gui::views::RoundedRectangle>("CustomGeometry", 1, 0, "RoundedRectangle");
}

static void registerEnums()
{
    qmlRegisterType<duly_gui::qmlresources::IoTypeRessouce>("Utils", 1, 0, "IOType");
    qmlRegisterType<duly_gui::qmlresources::FlowTypeRessouce>("Utils", 1, 0, "FlowType");
    qmlRegisterType<duly_gui::qmlresources::DeclarationTypeRessouce>("Utils", 1, 0, "DeclarationType");

}

static void registerUtils()
{
    qmlRegisterSingletonType<duly_gui::Manager>("Utils", 1, 0, "Manager", manager_singleton_provider);
    qmlRegisterSingletonType<duly_gui::DulySettings>("Utils", 1, 0, "DulySettings", settings_singleton_provider);
    qmlRegisterSingletonType<QCStandardPaths>("Utils", 1, 0, "StandardPath", standardpath_singleton_provider);

    qmlRegisterType<duly_gui::views::Console>("Utils", 1, 0, "Console");
    qmlRegisterType<duly_gui::models::DulySettingsModel>("Utils", 1, 0, "DulySettingsModel");
    qmlRegisterType<duly_gui::models::QCanvas>("Utils", 1, 0, "QCanvas");
    qmlRegisterType<duly_gui::models::QGrid>("Utils", 1, 0, "QGrid");
    qmlRegisterType<duly_gui::models::QBorder>("Utils", 1, 0, "QBorder");
    qmlRegisterType<duly_gui::models::QNode>("Utils", 1, 0, "QNode");
    qmlRegisterType<duly_gui::models::QNodes>("Utils", 1, 0, "QNodes");
    qmlRegisterType<duly_gui::models::QDeclaration>("Utils", 1, 0, "QDeclaration");
    qmlRegisterType<duly_gui::models::QDeclarationView>("Utils", 1, 0, "QDeclarationView");
    qmlRegisterType<duly_gui::models::QTextSettings>("Utils", 1, 0, "QTextSettings");
    qmlRegisterType<duly_gui::models::QFontSettings>("Utils", 1, 0, "QFontSettings");
    qmlRegisterType<duly_gui::models::MenuSettings>("Utils", 1, 0, "MenuSettings");
    qmlRegisterType<duly_gui::models::QBackground>("Utils", 1, 0, "QBackground");
//    qRegisterMetaType<duly_gui::models::TreeModel*>("TreeModel*");
//    qmlRegisterType<duly_gui::models::Common>("Utils", 1, 0, "Common");

    qmlRegisterType<duly_gui::models::TreeModel>("Utils", 1, 0, "TreeModel");
    qmlRegisterType<duly_gui::models::TreeItem>("Utils", 1, 0, "TreeItem");
    qmlRegisterType<duly_gui::models::NameSpaceBarItem>("Utils", 1, 0, "NameSpaceBarItem");
    qmlRegisterType<duly_gui::models::NameSpaceBarModel>("Utils", 1, 0, "NameSpaceBarModel");
    qmlRegisterType<duly_gui::models::User>("Utils", 1, 0, "User");

    qmlRegisterType<duly_gui::models::DeclarationModel>("Utils", 1, 0, "DeclarationModel");
    qmlRegisterType<duly_gui::models::Declaration>("Utils", 1, 0, "Declaration");
//    qmlRegisterType<DeclarationColumnModel>("Utils", 1, 0, "DeclarationColumnModel");
//    qmlRegisterType<duly_gui::models::TreeItem>("Utils", 1, 0, "TreeItem");
}



static void registerQml()
{
    registerUtils();
    registerEnums();
    registerCustomViews();
    registerCustomGeometry();
    registerCustomConnection();
}

int main(int argc, char *argv[])
{
    registerQml();
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    duly_gui::DulyApp app(argc, argv);

    QQmlApplicationEngine engine;
    app.registerEngine(&engine);
    app.initApp();

//    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
//    if (engine.rootObjects().isEmpty())
//        return -1;

    // DEBUT CODE POUR LA COMMUNICATION CLIENT SERVER

//    ClientCommunication com(QHostAddress::LocalHost, 7777, "Duly GUI");
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

    return app.exec();
}
