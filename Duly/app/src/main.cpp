#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTimer>
#include <functional>

#include "views.h"

#include "controllers/consolecontroller.h"
#include "dulyapp.h"
#include "manager.h"

#include "include/clientcommunication.h"
#include "include/testconnection.h"
#include "include/eventconsumer.h"
#include "include/clientmanager.h"

struct RegisterSettings
{
	RegisterSettings(const char* namespaceName, int version, int subVersion)
        : NamespaceName(namespaceName), version(version), subVersion(subVersion) {}

	const char *NamespaceName;
	const int version;
	const int subVersion;
};

void registerCustomConnection() {
    qmlRegisterType<EventConsumer>("Communication.EventConsumer", 1, 0, "EventConsumer");
}

void registerCustomViews()
{
    const RegisterSettings s = { "CustomViews", 1, 0 };

    qmlRegisterType<duly_gui::views::DulyCanvas>(s.NamespaceName, s.version, s.subVersion, "DulyCanvas");
    qmlRegisterType<duly_gui::views::GenericNode>(s.NamespaceName, s.version, s.subVersion, "GenericNode");
    qmlRegisterType<duly_gui::views::Input>(s.NamespaceName, s.version, s.subVersion, "Input");
    qmlRegisterType<duly_gui::views::Output>(s.NamespaceName, s.version, s.subVersion, "Output");
    qmlRegisterType<duly_gui::views::Flow>(s.NamespaceName, s.version, s.subVersion, "Flow");
}
void registerCustomGeometry()
{
    const RegisterSettings s = { "CustomGeometry", 1, 0 };

	qmlRegisterType<duly_gui::views::BezierCurve>(s.NamespaceName, s.version, s.subVersion, "BezierCurve");
	qmlRegisterType<duly_gui::views::Line>(s.NamespaceName, s.version, s.subVersion, "Line");
	qmlRegisterType<duly_gui::views::RoundedRectangle>(s.NamespaceName, s.version, s.subVersion, "RoundedRectangle");
    qmlRegisterType<duly_gui::views::DulyCanvas>(s.NamespaceName, s.version, s.subVersion, "DulyCanvas");
    qmlRegisterType<DulyResources>(s.NamespaceName, s.version, s.subVersion, "IOType");
}

void registerDulyUtils()
{
    const RegisterSettings s = { "DulyUtils", 1, 0 };

    qmlRegisterType<duly_gui::views::Console>(s.NamespaceName, s.version, s.subVersion, "Console");
}

static QObject *manager_singleton_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return new duly_gui::Manager();
}

void registerQml()
{
    registerCustomViews();
    registerCustomGeometry();
    registerDulyUtils();
    registerCustomConnection();

    qmlRegisterSingletonType<duly_gui::Manager>("Tools", 1, 0, "Manager", manager_singleton_provider);
}

int main(int argc, char *argv[])
{
    registerQml();
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    duly_gui::DulyApp app(argc, argv);

    app.setOrganizationName("Duly");
    app.setOrganizationDomain("Duly.com");

    ClientCommunication *com = ClientManager::shared().newClient(QHostAddress::LocalHost, 7777, "Duly GUI");

    app.setApplicationName("Duly Application");

    QQmlApplicationEngine engine;

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    QSettings settings("folderName", "fileName");

    // DEBUT CODE POUR LA COMMUNICATION CLIENT SERVER

//    ClientCommunication com(QHostAddress::LocalHost, 7777, "Duly GUI");
//    com.start();

    TestConnection test(*com);

   // com->registerEvent("DECLARE", 1, std::bind(&TestConnection::onReceiveEventPopole, &test, std::placeholders::_1, std::placeholders::_2));

   QTimer *timer = new QTimer();
      QObject::connect(timer, SIGNAL(timeout()), &test, SLOT(update()));
      timer->start(1000);


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
