#include "dnai/editor.h"
#include "dnai/solution.h"
#include "dnai/project.h"
#include "dnai/exceptions/notimplemented.h"

namespace dnai
{
	const QString& Editor::version() const
	{
		return m_version;
	}

	void Editor::setVersion(const QString& version)
	{
		if (version == m_version)
			return;
		m_version = version;
	}

	void Editor::save()
	{
		m_solution->save();
	}

	void Editor::restoreViewState(const QJsonObject& obj)
	{
		throw exceptions::NotImplemented();
	}

	void Editor::saveViewState()
	{
		QJsonObject obj;
		QJsonArray arr;
		for (const auto view : m_viewZones)
		{
			QJsonObject var;
			view->serialize(var);
			arr.append(var);
		}
		obj["views"] = arr;
	}

	void Editor::openSolution(const QString& filename)
	{
		m_solution = new Solution();
		m_solution->load(filename);
	}

	void Editor::closeSolution()
	{
		m_solution->close();
	}

	const QList<interfaces::ICommand*>& Editor::getActions() const
	{
		return m_actions;
	}

	const QObject& Editor::getSelection() const
	{
		return *m_selection;
	}

	const QList<QObject*>& Editor::getSelections() const
	{
		return m_selections;
	}

	const QList<interfaces::IViewZone *>& Editor::getViews() const
	{
		return m_viewZones;
	}

	const interfaces::IViewZone& Editor::getSelectedView() const
	{
		return *m_seletedItem;
	}

	const interfaces::ISolution& Editor::getSolution() const
	{
		return *m_solution;
	}

	Project* Editor::project() const
	{
		return dynamic_cast<Project *>(m_solution->seletedProject());
	}

	void Editor::setProject(Project* proj)
	{
		if (m_solution->selectProject(proj))
			emit projectChanged(proj);
	}
}
