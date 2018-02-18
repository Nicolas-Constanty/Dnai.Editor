#ifndef APP_H
#define APP_H

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDir>
#include "settings.h"
#include "processmanager.h"
#include "views/appview.h"
#include "views/instructionview.h"

namespace dnai {
    class App : public QGuiApplication
    {
        Q_OBJECT
    public:
        App(int & argc, char **argv);
        ~App();

        void loadMainWindow();
	    bool eventFilter(QObject* o, QEvent* event) override;
        void registerSettings(AppSettings* appSetting);
		QQmlApplicationEngine const* engine() const;
        AppSettings* settings() const;

	    views::AppView *appView() const;

    public slots:
        void initApp();

    public:
        static void loadFonts();
        static App *currentInstance();
	    static QObject *createQmlObject(const QString &path);
        static QQmlEngine *getEngineInstance();
		static views::InstructionView *instructionView();

    private:
        QQmlApplicationEngine m_engine;
        AppSettings *m_settings;
        ProcessManager* m_processManager;
	    views::AppView* m_appView;
	    static App *m_instance;

        void initProcessManager();
        QObject *createQmlComponent(const QString &path);
	    static void setupSettings();
		void initAppView();

    };
}

#endif // APP_H
