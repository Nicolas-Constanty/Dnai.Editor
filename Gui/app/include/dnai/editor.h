#ifndef DNAI_EDITOR_H
#define DNAI_EDITOR_H

#include <QQuickItem>
#include "interfaces/ieditor.h"
#include "dnai/views/editorview.h"
#include "dnai/solution.h"
#include "models/entity.h"
#include "models/basicnodemodel.h"
#include "dnai/toastermanagerservice.h"

namespace dnai
{
	class App;
    class Project;
    class Session;
    class PropertyPanelProperties : public QObject {
        Q_OBJECT
        Q_PROPERTY(QStringList visibility READ visibility CONSTANT)
        Q_PROPERTY(QStringList entityType READ entityType CONSTANT)
        Q_PROPERTY(QStringList varType READ varType CONSTANT)
    public:
        explicit PropertyPanelProperties(QObject *parent = nullptr);

        const QStringList &visibility() const;
        const QStringList &entityType() const;
        const QStringList &varType() const;

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

	protected:
		Editor() = default;
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
        Q_INVOKABLE void registerEditorView(views::EditorView *view);

        Q_INVOKABLE const QList<QQuickItem *>& views() const override;
        Q_INVOKABLE QQuickItem *selectedView() const override;
        Q_INVOKABLE void selectView(QQuickItem *i);
		Q_INVOKABLE void createNode(dnai::models::Entity* entity, QObject* nodeModel, qint32 x, qint32 y) const;

        Q_INVOKABLE void openSolution() override;
        Q_INVOKABLE void loadSolution(const QString& filename) override;
        Q_INVOKABLE void notifyInformation(QString const &, std::function<void ()> func);
        Q_INVOKABLE void notifySuccess(QString const &text, std::function<void ()> func);
        Q_INVOKABLE void notifyError(QString const &text, std::function<void ()> func);
        Q_INVOKABLE void notifyWarning(QString const &text, std::function<void ()> func);

        Q_INVOKABLE void startApp();
        Q_INVOKABLE static void checkVersion();
        Q_INVOKABLE void registerMainView(QObject *);
        Q_INVOKABLE void createSolution(const QString &name,
                                        const QString &description,
                                        const QString &path,
                                        const QString &proj_name,
                                        const QString &proj_desc);
        Q_INVOKABLE QQuickWindow *mainView();
        Q_INVOKABLE void registerPropertyView(QQuickItem *view);
		Q_INVOKABLE QQuickItem* propertyView() const;
		Q_INVOKABLE void loadFunction(dnai::models::Entity *entity) const;

	public:
		void selectProject(Project *proj);
		static Editor &instance();

    public:
        void setSolution(dnai::Solution *sol);
        models::BasicNodeModel *nodes() const;
        PropertyPanelProperties *propertyPanelProperties();
        Session *session() const;
	signals:
		void solutionChanged(dnai::Solution *proj);

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
		PropertyPanelProperties *m_propertyPanelProperties = nullptr;

		static Editor &m_instance;
	};
	}

#endif //DNAI_EDITOR_H
