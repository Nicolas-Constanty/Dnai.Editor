#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QDebug>
#include <QtGui>
#include <QtQuick>

#include "beziercurve.h"
#include "line.h"
#include "dulycanvas.h"

int main(int argc, char *argv[])
{

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    qmlRegisterType<BezierCurve>("CustomGeometry", 1, 0, "BezierCurve");
    qmlRegisterType<Line>("CustomGeometry", 1, 0, "Line");
    qmlRegisterType<DulyCanvas>("CustomGeometry", 1, 0, "DulyCanvas");
    app.setOrganizationName("Duly");
    app.setOrganizationDomain("Duly.com");
    app.setApplicationName("Duly Application");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    QSettings settings("folderName", "fileName");
    qDebug() << settings.fileName();

    return app.exec();
}
