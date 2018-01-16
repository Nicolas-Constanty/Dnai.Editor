#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTimer>
#include <functional>
#include "views.h"

#include "controllers/consolecontroller.h"
#include "dulyapp.h"
#include "manager.h"

#include "processmanager.h"

#include "include/controllers/clientcontroller.h"
#include "include/eventconsumer.h"

#include "dulysettings.h"
#include "dulysettingsmodel.h"

#include "models/treemodel.h"

static QObject *manager_singleton_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return new duly_gui::Manager();
}

static QObject *manager_singleton_provider_settings(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return new duly_gui::DulySettings();
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

static void registerUtils()
{
    qmlRegisterSingletonType<duly_gui::Manager>("Utils", 1, 0, "Manager", manager_singleton_provider);
    qmlRegisterSingletonType<duly_gui::DulySettings>("Utils", 1, 0, "DulySettings", manager_singleton_provider_settings);
    qmlRegisterType<IoTypeRessouce>("Utils", 1, 0, "IOType");
    qmlRegisterType<FlowTypeRessouce>("Utils", 1, 0, "FlowType");
    qmlRegisterType<DeclarationTypeRessouce>("Utils", 1, 0, "DeclarationType");
    qmlRegisterType<duly_gui::views::Console>("Utils", 1, 0, "Console");
    qmlRegisterType<duly_gui::DulySettingsModel>("Utils", 1, 0, "DulySettingsModel");
    qmlRegisterType<duly_gui::QCanvas>("Utils", 1, 0, "QCanvas");
    qmlRegisterType<duly_gui::QGrid>("Utils", 1, 0, "QGrid");
    qmlRegisterType<duly_gui::QBorder>("Utils", 1, 0, "QBorder");
    qmlRegisterType<duly_gui::QNode>("Utils", 1, 0, "QNode");
    qmlRegisterType<duly_gui::QNodes>("Utils", 1, 0, "QNodes");
    qmlRegisterType<duly_gui::QDeclaration>("Utils", 1, 0, "QDeclaration");
    qmlRegisterType<duly_gui::QDeclarationView>("Utils", 1, 0, "QDeclarationView");
    qmlRegisterType<duly_gui::QTextSettings>("Utils", 1, 0, "QTextSettings");
    qmlRegisterType<duly_gui::QFontSettings>("Utils", 1, 0, "QFontSettings");
//    qRegisterMetaType<duly_gui::models::TreeModel*>("TreeModel*");
    qmlRegisterType<duly_gui::models::TreeModel>("Utils", 1, 0, "TreeModel");
    qmlRegisterType<NameSpaceBarItem>("Utils", 1, 0, "NameSpaceBarItem");
    qmlRegisterType<NameSpaceBarModel>("Utils", 1, 0, "NameSpaceBarModel");
//    qmlRegisterType<duly_gui::models::TreeItem>("Utils", 1, 0, "TreeItem");
}



static void registerQml()
{
    registerUtils();
    registerCustomViews();
    registerCustomGeometry();
    registerCustomConnection();
}

int main(int argc, char *argv[])
{
    registerQml();
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	
	duly_gui::DulyApp app(argc, argv);

	app.initApp();

#ifdef Q_OS_MAC
    ProcessManager processManager("./settings/conf/mac/bin_info.cfg");
#else
    ProcessManager processManager("./settings/conf/windows/bin_info.cfg");
#endif

    processManager.launch();


    ClientController::serverPort = processManager.getServerPort();
    ClientController::shared();


    QQmlApplicationEngine engine;
	app.registerEngine(&engine);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

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
