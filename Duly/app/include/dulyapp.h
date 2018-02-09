#ifndef DULYAPP_H
#define DULYAPP_H

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDir>
#include "dulysettings.h"
#include "project.h"
#include "views/dulycanvas.h"
#include "models/treemodel.h"


namespace duly_gui {
	class DulyApp : public QGuiApplication
    {
        Q_OBJECT
	public:
        DulyApp(int & argc, char **argv);
		void registerEngine(QQmlApplicationEngine *engine);
        void loadFonts();
		QQmlApplicationEngine* engine() const { return m_engine; }
		static views::DulyCanvas* currentCanvasInstance();
		bool eventFilter(QObject *object, QEvent *event) override;
		void registerSettings(DulySettings* dulySettings);
		DulySettings *settings() const { return m_settings; }
		views::DulyCanvas *currentCanvas() const { return m_currentCanvas; }
		void registerCanvas(views::DulyCanvas *c);
		void setCurrentCanvas(views::DulyCanvas *c);

    public slots:
        void initApp();
        void loadMainWindow();

    private:
		DulySettings *m_settings;
		QList<views::DulyCanvas *> m_canvases;
		views::DulyCanvas *m_currentCanvas;
        QQmlApplicationEngine* m_engine;
        void initProcessManager();
        void setupSettings();
    };
}

#endif // DULYAPP_H
