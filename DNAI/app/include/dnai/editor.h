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
	class Editor : public QObject, public interfaces::IEditor
	{
		Q_OBJECT
        Q_PROPERTY(dnai::Solution *solution READ getSolution WRITE setSolution NOTIFY solutionChanged)
        Q_PROPERTY(dnai::models::BasicNodeModel *nodes READ nodes CONSTANT)
        Q_PROPERTY(dnai::Session *session READ session CONSTANT)

	protected:
		Editor() = default;
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
		void registerEditorView(views::EditorView *view);

        Q_INVOKABLE const QList<QQuickItem *>& views() const override;
        Q_INVOKABLE QQuickItem *selectedView() const override;
        Q_INVOKABLE void selectView(QQuickItem *i);
        Q_INVOKABLE void createNode(QObject* nodeModel) const;
        Q_INVOKABLE void openSolution() override;
        Q_INVOKABLE void loadSolution(const QString& filename) override;
        Q_INVOKABLE void notifyInformation(QString const &, std::function<void ()> func);
        Q_INVOKABLE void notifySuccess(QString const &text, std::function<void ()> func);
        Q_INVOKABLE void notifyError(QString const &text, std::function<void ()> func);
        Q_INVOKABLE void notifyWarning(QString const &text, std::function<void ()> func);

        Q_INVOKABLE void startApp();
        Q_INVOKABLE void checkVersion();
        Q_INVOKABLE void registerMainView(QObject *);
        QQuickItem *mainView();

	public:
		void selectProject(Project *proj);
		static Editor &instance();

    public:
        void setSolution(dnai::Solution *sol);
        models::BasicNodeModel *nodes() const;
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
        QQuickItem *m_mainView = nullptr;

        static Editor &m_instance;
	};
}

#endif //DNAI_EDITOR_H
