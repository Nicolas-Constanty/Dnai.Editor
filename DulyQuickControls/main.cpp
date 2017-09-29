#include <QtGui>
#include <QtQuick>

#include "beziercurve.h"
#include "line.h"
#include "dulycanvas.h"
#include "roundedrectangle.h"
#include "input.h"
#include "output.h"

int main(int argc, char *argv[])
{

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    qmlRegisterType<BezierCurve>("CustomGeometry", 1, 0, "BezierCurve");
    qmlRegisterType<Line>("CustomGeometry", 1, 0, "Line");
    qmlRegisterType<DulyCanvas>("CustomGeometry", 1, 0, "DulyCanvas");
    qmlRegisterType<RoundedRectangle>("CustomGeometry", 1, 0, "RoundedRectangle");
//    qmlRegisterType<Input>("CustomGeometry", 1, 0, "IO");
    qmlRegisterType<Input>("CustomGeometry", 1, 0, "Input");
    qmlRegisterType<Output>("CustomGeometry", 1, 0, "Output");
    qmlRegisterType<DulyResources>("CustomGeometry", 1, 0, "IOType");
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
