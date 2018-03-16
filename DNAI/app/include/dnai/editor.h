#ifndef DNAI_EDITOR_H
#define DNAI_EDITOR_H

#include "interfaces/ieditor.h"

namespace dnai
{
    class Project;
    class Solution;
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
		Q_INVOKABLE const QList<interfaces::IViewZone *>& views() const override;
		const interfaces::IViewZone& selectedView() const override;
        interfaces::ISolution *solution() const override;
        dnai::Solution *getSolution() const;

	public:
		void selectProject(Project *proj);
		static Editor &instance();

    public:
        void setSolution(dnai::Solution *sol);

	signals:
        void solutionChanged(dnai::Solution *proj);

	private:
		interfaces::ISolution *m_solution;
		interfaces::IViewZone * m_seletedItem = nullptr;
		QList<interfaces::IViewZone*> m_viewZones;
		QList<QObject*> m_selections;
		QObject *m_selection;
		QList<interfaces::ICommand*> m_actions;
		QString m_version = "0.0.1";
		static Editor &m_instance;
	};
}

#endif //DNAI_EDITOR_H
