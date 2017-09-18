#include <QApplication>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QDebug>

#include "dulyscene.h"

//#include <QGraphicsView>
//#include <QGraphicsScene>

int main(int argc, char *argv[])
{
    //QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    app.setOrganizationName("Duly");
    app.setOrganizationDomain("Duly.com");
    app.setApplicationName("Duly Application");

    qmlRegisterType<DulyScene>("DulyScene", 1, 0, "DulyScene");

//    DulyScene dulyScene;


   // (void)scene;

    QQmlApplicationEngine engine;

//    QGraphicsScene scene;

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    QSettings settings("folderName", "fileName");
    qDebug() << settings.fileName();

    return app.exec();
}
