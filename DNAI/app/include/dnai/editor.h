#ifndef DNAI_EDITOR_H
#define DNAI_EDITOR_H

#include "interfaces/ieditor.h"
#include "dnai/views/editorview.h"
#include "dnai/solution.h"
#include "models/entity.h"

namespace dnai
{
	class App;
    class Project;
	class Editor : public QObject, public interfaces::IEditor
	{
		Q_OBJECT
        Q_PROPERTY(dnai::Solution *solution READ getSolution WRITE setSolution NOTIFY solutionChanged)
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
		Q_INVOKABLE void openSolution() override;
		Q_INVOKABLE void loadSolution(const QString& filename) override;
		void closeSolution() override;
		const QList<interfaces::ICommand*>& actions() const override;
		const QObject& selection() const override;
		const QList<QObject*>& selections() const override;
		Q_INVOKABLE const QList<QQuickItem *>& views() const override;
		Q_INVOKABLE QQuickItem *selectedView() const override;
		Q_INVOKABLE void selectView(QQuickItem *i);
		interfaces::ISolution *solution() const override;
        dnai::Solution *getSolution() const;
		void addView(QQuickItem* v) override;
		views::EditorView *mainView() const;
		void registerEditorView(views::EditorView *view);
		Q_INVOKABLE static dnai::App *app();

	public:
		void selectProject(Project *proj);
		static Editor &instance();

    public:
        void setSolution(dnai::Solution *sol);

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
		static Editor &m_instance;
	};
}

#endif //DNAI_EDITOR_H
