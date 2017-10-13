#include <QtGui>
#include <QtQuick>
#include <QQuickStyle>

#include "beziercurve.h"
#include "line.h"
#include "dulycanvas.h"
#include "roundedrectangle.h"
#include "input.h"
#include "output.h"
#include "genericnode.h"
#include "flow.h"

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

	qmlRegisterType<duly_gui::BezierCurve>(s.NamespaceName, s.version, s.subVersion, "BezierCurve");
	qmlRegisterType<duly_gui::Line>(s.NamespaceName, s.version, s.subVersion, "Line");
	qmlRegisterType<duly_gui::DulyCanvas>(s.NamespaceName, s.version, s.subVersion, "DulyCanvas");
	qmlRegisterType<duly_gui::RoundedRectangle>(s.NamespaceName, s.version, s.subVersion, "RoundedRectangle");
	qmlRegisterType<duly_gui::GenericNode>(s.NamespaceName, s.version, s.subVersion, "GenericNode");
	qmlRegisterType<duly_gui::Input>(s.NamespaceName, s.version, s.subVersion, "Input");
	qmlRegisterType<duly_gui::Output>(s.NamespaceName, s.version, s.subVersion, "Output");
    qmlRegisterType<DulyResources>(s.NamespaceName, s.version, s.subVersion, "IOType");
    qmlRegisterType<duly_gui::Flow>(s.NamespaceName, s.version, s.subVersion, "Flow");
}

int main(int argc, char *argv[])
{

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Material");
    
	registerCustomGeometry();

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
