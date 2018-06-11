#ifndef DNAI_EDITOR_H
#define DNAI_EDITOR_H

#include <queue>
#include <tuple>

#include <QQuickItem>
#include "interfaces/ieditor.h"
#include "dnai/views/editorview.h"
#include "dnai/solution.h"
#include "models/entity.h"
#include "models/basicnodemodel.h"
#include "dnai/toastermanagerservice.h"
#include "dnai/models/contextmenu.h"
#include "dnai/models/contextMenuModel.h"

namespace dnai
{
    class App;
    class Project;
    class Session;

	class PropertyPanelProperties : public QObject {
		Q_OBJECT
        Q_PROPERTY(QStringList visibility READ visibility CONSTANT)
        Q_PROPERTY(QStringList entityType READ entityType CONSTANT)
        Q_PROPERTY(dnai::models::gui::declarable::VarTypeList *varTypes READ varTypes CONSTANT)

	public:
		explicit PropertyPanelProperties(QObject *parent = nullptr);

		const QStringList &visibility() const;
		const QStringList &entityType() const;
		models::gui::declarable::VarTypeList *varTypes() const;

	private:
		QStringList m_visibility;
		QStringList m_entityType;
	};

	class Editor : public QObject, public interfaces::IEditor
	{
		Q_OBJECT
        Q_PROPERTY(dnai::Solution *solution READ getSolution WRITE setSolution NOTIFY solutionChanged)
        Q_PROPERTY(dnai::models::BasicNodeModel *nodes READ nodes CONSTANT)
        Q_PROPERTY(dnai::Session *session READ session CONSTANT)  
		Q_PROPERTY(dnai::PropertyPanelProperties *propertyPanelProperties READ propertyPanelProperties CONSTANT)
		Q_PROPERTY(dnai::models::ContextMenu *contextMenu READ contextMenu CONSTANT)
        Q_PROPERTY(bool loaded READ loaded WRITE setLoaded NOTIFY loadedChanged)
        Q_PROPERTY(QString solutionName READ solutionName)
		Q_PROPERTY(dnai::models::ContextMenuModel *contextMenuModel READ contextMenuModel CONSTANT)

    protected:
        Editor();
        ~Editor();
    public:
        Editor(Editor const&) = delete;             // Copy construct
        Editor(Editor&&) = delete;                  // Move construct
        Editor& operator=(Editor const&) = delete;  // Copy assign
        Editor& operator=(Editor &&) = delete;      // Move assign
        const QString& version() const override;
        void setVersion(const QString& version) override;
        void save() override;
        void restoreViewState(const QJsonObject& obj) override;
        void saveViewState() override;
        void closeSolution() override;

        const QList<interfaces::ICommand*>& actions() const override;
        const QObject& selection() const override;
        const QList<QObject*>& selections() const override;
        interfaces::ISolution *solution() const override;
        dnai::Solution *getSolution() const;
        void addView(QQuickItem* v) override;
        views::EditorView *mainView() const;
        bool loaded() const;
        dnai::models::ContextMenu *contextMenu() const;
        QString const &solutionName() const;
		dnai::models::ContextMenuModel* contextMenuModel();

        void setLoaded(bool);
        Q_INVOKABLE void registerEditorView(views::EditorView *view);

        Q_INVOKABLE const QList<QQuickItem *>& views() const override;
        Q_INVOKABLE QQuickItem *selectedView() const override;
        Q_INVOKABLE bool isSolutionLoad() const;
        Q_INVOKABLE void selectView(QQuickItem *i);
        Q_INVOKABLE void createNode(dnai::models::Entity* entity, dnai::models::ContextMenuItem *node, qint32 x, qint32 y);

        Q_INVOKABLE void openSolution() override;
        Q_INVOKABLE void loadSolution(const QString& filename) override;
        Q_INVOKABLE void newEditor(const QString &solutionToLoad = "");
        Q_INVOKABLE void notifyInformation(QString const &, std::function<void ()> func = [](){});
        Q_INVOKABLE void notifySuccess(QString const &text, std::function<void ()> func = []() {});
        Q_INVOKABLE void notifyError(QString const &text, std::function<void ()> func = []() {});
        Q_INVOKABLE void notifyWarning(QString const &text, std::function<void ()> func = []() {});

        Q_INVOKABLE void onBuildSuccess();

        Q_INVOKABLE void startApp();
        Q_INVOKABLE static void checkVersion();
		//Q_INVOKABLE static dnai::models::EntityList *entities();
		Q_INVOKABLE void registerMainView(QObject *);
        Q_INVOKABLE void addProject(QString const &proj_name, QString const &proj_desc);
        Q_INVOKABLE bool createSolution(const QString &name,
		                                const QString &description,
		                                const QString &path,
		                                const QString &proj_name,
		                                const QString &proj_desc);
		Q_INVOKABLE QQuickWindow *mainView();
		Q_INVOKABLE void registerPropertyView(QQuickItem *view);
		Q_INVOKABLE QQuickItem* propertyView() const;
		Q_INVOKABLE void loadFunction(dnai::models::Entity *entity) const;
		Q_INVOKABLE void updateContextMenu(dnai::models::Entity *entity) const;

	public:
		void selectProject(Project *proj);
		static Editor &instance();
		PropertyPanelProperties *propertyPanelProperties();

    public:
        void setSolution(dnai::Solution *sol);
        models::BasicNodeModel *nodes() const;
        Session *session() const;

    public:
        void setAppName(QString const &name);
        void setSolutionName(QString const &name);

    signals:
        void solutionChanged(dnai::Solution *proj);
        void loadedChanged(bool);

    private:
		QQuickItem * createNodeQMLComponent(models::ContextMenuItem *node, models::Entity *func, models::gui::Instruction *instruction, QQuickItem *parent) const;

    public slots:
        void onInstructionAdded(models::Entity *func, models::gui::Instruction *instr);
        void onAddInstructionError(quint32 func, quint32 type, QList<quint32> const &args, QString const &msg);
        void onEntityDeclared(dnai::models::Entity *declared);

    private:
        interfaces::ISolution *m_solution;
        QQuickItem * m_seletedItem = nullptr;
        QList<QQuickItem *> m_viewZones;
        QList<QObject*> m_selections;
        QObject *m_selection;
        QList<interfaces::ICommand*> m_actions;
        QString m_version = "0.0.1";
        views::EditorView *m_editorView;
        ToasterManagerService m_toasterManagerService;
        QQuickWindow *m_mainView = nullptr;
        QQuickItem* m_propertyView;
        models::ContextMenu* m_contextMenu;
		dnai::PropertyPanelProperties *m_propertyPanelProperties;
        QString m_appname;
        QString m_solutionName;
		dnai::models::ContextMenuModel *m_contextMenuModel;

    private:
        std::queue<std::tuple<models::ContextMenuItem *, quint32, quint32>> m_pendingInstruction;
        bool m_loaded = false;

    private:
        static Editor &m_instance;
    };
    }

#endif //DNAI_EDITOR_H
