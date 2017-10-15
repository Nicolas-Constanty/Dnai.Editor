#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "views/beziercurve.h"
#include "views/line.h"
#include "views/dulycanvas.h"
#include "views/roundedrectangle.h"
#include "views/input.h"
#include "views/output.h"
#include "views/genericnode.h"
#include "views/flow.h"
#include "views/console.h"
#include "controllers/consolecontroller.h"
#include "dulyapp.h"

struct RegisterSettings
{
	RegisterSettings(const char* namespaceName, int version, int subVersion)
		: NamespaceName(namespaceName),
		  version(version),
		  subVersion(subVersion)
	{
	}

	const char *NamespaceName;
	const int version;
	const int subVersion;
};

void registerCustomGeometry()
{
    const RegisterSettings s = { "CustomGeometry", 1, 0 };

	qmlRegisterType<duly_gui::views::BezierCurve>(s.NamespaceName, s.version, s.subVersion, "BezierCurve");
	qmlRegisterType<duly_gui::views::Line>(s.NamespaceName, s.version, s.subVersion, "Line");
	qmlRegisterType<duly_gui::views::DulyCanvas>(s.NamespaceName, s.version, s.subVersion, "DulyCanvas");
	qmlRegisterType<duly_gui::views::RoundedRectangle>(s.NamespaceName, s.version, s.subVersion, "RoundedRectangle");
	qmlRegisterType<duly_gui::views::GenericNode>(s.NamespaceName, s.version, s.subVersion, "GenericNode");
	qmlRegisterType<duly_gui::views::Input>(s.NamespaceName, s.version, s.subVersion, "Input");
	qmlRegisterType<duly_gui::views::Output>(s.NamespaceName, s.version, s.subVersion, "Output");
    qmlRegisterType<DulyResources>(s.NamespaceName, s.version, s.subVersion, "IOType");
    qmlRegisterType<duly_gui::views::Flow>(s.NamespaceName, s.version, s.subVersion, "Flow");
}

void registerDulyUtils()
{
    const RegisterSettings s = { "DulyUtils", 1, 0 };

    qmlRegisterType<duly_gui::views::Console>(s.NamespaceName, s.version, s.subVersion, "Console");
}

int main(int argc, char *argv[])
{
    registerCustomGeometry();
    registerDulyUtils();

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    duly_gui::DulyApp app(argc, argv);

    app.setOrganizationName("Duly");
    app.setOrganizationDomain("Duly.com");
    app.setApplicationName("Duly Application");

    QQmlApplicationEngine engine;

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    QSettings settings("folderName", "fileName");
    return app.exec();
}
