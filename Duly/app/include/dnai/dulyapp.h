#ifndef DULYAPP_H
#define DULYAPP_H

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDir>
#include "dulysettings.h"
#include "views/dulycanvas.h"
#include "processmanager.h"

namespace dnai {
	class DulyApp : public QGuiApplication
    {
        Q_OBJECT
	public:
        DulyApp(int & argc, char **argv);
		bool eventFilter(QObject * o, QEvent *event) override;
		void registerSettings(DulySettings* dulySettings);
		QQmlApplicationEngine const* engine() const;
		DulySettings *settings() const;
		views::DulyCanvas *currentCanvas() const;
		void registerCanvas(views::DulyCanvas *c);
		void setCurrentCanvas(views::DulyCanvas *c);
		void loadMainWindow();
		static void loadFonts();
		static views::DulyCanvas* currentCanvasInstance();
		static DulyApp *currentInstance();
		static QObject *createQmlObject(const QString &path);
		static QQmlEngine *getEngineInstance();
    public slots:
        void initApp();

    private:
		QQmlApplicationEngine m_engine;
		DulySettings *m_settings;
		QList<views::DulyCanvas *> m_canvases;
		views::DulyCanvas *m_currentCanvas;
		ProcessManager* m_processManager{};
		void initProcessManager();
		QObject *createQmlComponent(const QString &path);
		static void setupSettings();
		static DulyApp *m_instance;
    };
}

#endif // DULYAPP_H
