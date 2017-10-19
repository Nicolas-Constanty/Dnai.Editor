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
		: namespaceName(namespaceName),
		  version(version),
		  subVersion(subVersion)
	{
	}

	const char *namespaceName;
	const int version;
	const int subVersion;
};

void registerCustomGeometry()
{
	const RegisterSettings s = { "CustomGeometry", 1, 0 };

	qmlRegisterType<BezierCurve>(s.namespaceName, s.version, s.subVersion, "BezierCurve");
	qmlRegisterType<Line>(s.namespaceName, s.version, s.subVersion, "Line");
	qmlRegisterType<DulyCanvas>(s.namespaceName, s.version, s.subVersion, "DulyCanvas");
	qmlRegisterType<RoundedRectangle>(s.namespaceName, s.version, s.subVersion, "RoundedRectangle");
	qmlRegisterType<GenericNode>(s.namespaceName, s.version, s.subVersion, "GenericNode");
	qmlRegisterType<Input>(s.namespaceName, s.version, s.subVersion, "Input");
	qmlRegisterType<Output>(s.namespaceName, s.version, s.subVersion, "Output");
	qmlRegisterType<DulyResources>(s.namespaceName, s.version, s.subVersion, "IOType");
//    qmlRegisterType<DulyResources>(s.namespaceName, s.version, s.subVersion, "IOType");
    qmlRegisterType<Flow>(s.namespaceName, s.version, s.subVersion, "Flow");
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
