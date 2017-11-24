#ifndef DULYAPP_H
#define DULYAPP_H

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDir>

namespace duly_gui {
	class DulyApp : public QGuiApplication
    {
	public:
        DulyApp(int & argc, char **argv);
        bool eventFilter(QObject *object, QEvent *event) override;
		static void initApp();

	private:
		QSettings m_settings;
    };
}

#endif // DULYAPP_H
