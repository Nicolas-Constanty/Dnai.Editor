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
#include "iloadingclass.h"
#include "session.h"

namespace dnai {
    class App : public QGuiApplication, public ILoadingClass
    {
        Q_OBJECT
    public:
        App(int & argc, char **argv);
        ~App();

        void loadMainWindow();
	    bool eventFilter(QObject* o, QEvent* event) override;
		models::BasicNodeModel *basicNodesModel() const;
        void registerSettings(AppSettings* appSetting);
		QQmlApplicationEngine const* engine() const;
        AppSettings* settings() const;
		Session const * session() const;

	    views::AppView *appView() const;
        void initProcessManager();

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
		models::BasicNodeModel *m_nodeModel;
	    Session m_session;
	    static App *m_instance;

        QObject *createQmlComponent(const QString &path);
	    static void setupSettings();
		void initAppView();

    protected:
        std::queue<std::function<void()>> init() override;
    };
}

#endif // APP_H
