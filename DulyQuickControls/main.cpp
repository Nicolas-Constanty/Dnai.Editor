#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
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
