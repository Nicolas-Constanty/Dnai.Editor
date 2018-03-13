#ifndef DNAI_EDITOR_H
#define DNAI_EDITOR_H
#include "interfaces/ieditor.h"


namespace dnai
{
	class Project;
	class Editor : public QObject, public interfaces::IEditor<Editor>
	{
		Q_OBJECT
		Q_PROPERTY(dnai::Project *project READ project WRITE setProject NOTIFY projectChanged)
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
		void openSolution(const QString& filename) override;
		void closeSolution() override;
		const QList<interfaces::ICommand*>& getActions() const override;
		const QObject& getSelection() const override;
		const QList<QObject*>& getSelections() const override;
		const QList<interfaces::IViewZone *>& getViews() const override;
		const interfaces::IViewZone& getSelectedView() const override;
		const interfaces::ISolution& getSolution() const override;

	public:
		dnai::Project *project() const;
		void setProject(Project *proj);

	signals:
		void projectChanged(Project *proj);
		
	private:
		interfaces::ISolution *m_solution;
		interfaces::IViewZone * m_seletedItem = nullptr;
		QList<interfaces::IViewZone*> m_viewZones;
		QList<QObject*> m_selections;
		QObject *m_selection;
		QList<interfaces::ICommand*> m_actions;
		QString m_version;
	};
}

#endif //DNAI_EDITOR_H