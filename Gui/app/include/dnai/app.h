#ifndef APP_H
#define APP_H

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDir>
#include "processmanager.h"
#include "views/appview.h"
#include "views/instructionview.h"
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
        void versionsUpdater();
        void onNotifyVersionChanged();

    public:
        Session &session();
        views::AppView &appView() const;
	    QQmlApplicationEngine &engine();
        ProcessManager *processManager() const;
        Editor &editor() const;
        bool isNewVersionAvailable() const;
        qreal getSettingNumber(const QString &path);

    public:
        static void loadFonts();
        static App *currentInstance();
	    static QObject *createQmlObject(const QString &path);
        static QQmlEngine *getEngineInstance();
		static views::InstructionView *instructionView();

        Q_INVOKABLE void onBuildStart();
        Q_INVOKABLE bool isMac();

        void afterInit();
    public slots:
        void loadSplashScreen();
    private:
        QQmlApplicationEngine m_engine;
        ProcessManager* m_processManager;
	    views::AppView* m_appView;
        Session m_session;
	    static App *m_instance;
        Editor &m_editor;
        QString m_currentVersionAPI;
        QMap<QString, qreal> m_loadedNumbers;

        QObject *createQmlComponent(const QString &path);
	    static void setupSettings();
		void initAppView();

        void setVersion(const QString &ver);
        void setAPIVersion(const QString &ver);

    protected:
        std::queue<std::function<void()>> init() override;
    };
}

#endif // APP_H
