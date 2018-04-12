#ifndef APP_H
#define APP_H

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDir>
#include "settings.h"
#include "processmanager.h"
#include "views/appview.h"
#include "views/instructionview.h"
#include "models/basicnodemodel.h"
#include "dnai/interfaces/iloadingclass.h"
#include "session.h"
#include "editor.h"

namespace dnai {
    class App : public QGuiApplication, public interfaces::ILoadingClass
    {
		Q_OBJECT
    public:
        App(int & argc, char **argv);
		~App();

        void loadMainWindow();
		void initProcessManager();
	    bool eventFilter(QObject* o, QEvent* event) override;
        void registerSettings(AppSettings* appSettings);
        void versionsUpdater();

    public:
        Session &session();
        AppSettings &settings() const;
        views::AppView &appView() const;
	    QQmlApplicationEngine &engine();
        models::BasicNodeModel *nodes() const;
        Editor &editor() const;

    public:
        static void loadFonts();
        static App *currentInstance();
	    static QObject *createQmlObject(const QString &path);
        static QQmlEngine *getEngineInstance();
		static views::InstructionView *instructionView();

        Q_INVOKABLE void onBuildStart();
        Q_INVOKABLE bool isMac();

    private:
        QQmlApplicationEngine m_engine;
        AppSettings *m_settings;
        ProcessManager* m_processManager;
	    views::AppView* m_appView;
        models::BasicNodeModel *m_nodeModel;
	    Session m_session;
	    static App *m_instance;
        Editor &m_editor;
        QString m_currentVersion;
        QString m_currentVersionAPI;

        QObject *createQmlComponent(const QString &path);
	    static void setupSettings();
		void initAppView();

    protected:
        std::queue<std::function<void()>> init() override;
    };
}

#endif // APP_H
