#include "dnai/editor.h"
#include "dnai/solution.h"
#include "dnai/project.h"
#include "dnai/exceptions/notimplemented.h"

namespace dnai
{
	Editor &Editor::m_instance = *(new Editor());
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

	void Editor::openSolution()
	{
        for (auto proj : m_solution->projects())
            if (auto p = dynamic_cast<Project*>(proj))
                p->foreachEntity([](models::Entity *e) { e->declare(); });
	}

	void Editor::loadSolution(const QString& filename)
	{
		m_solution = new Solution();
		if (!filename.isEmpty())
			m_solution->load(filename);
	}

	void Editor::closeSolution()
	{
		m_solution->close();
	}

	const QList<interfaces::ICommand*>& Editor::actions() const
	{
		return m_actions;
	}

	const QObject& Editor::selection() const
	{
		return *m_selection;
	}

	const QList<QObject*>& Editor::selections() const
	{
		return m_selections;
	}

	const QList<interfaces::IViewZone *>& Editor::views() const
	{
		return m_viewZones;
	}

	const interfaces::IViewZone& Editor::selectedView() const
	{
		return *m_seletedItem;
	}

	void Editor::selectProject(Project* proj)
	{
		m_solution->selectProject(proj);
	}

	Editor& Editor::instance()
	{
        return m_instance;
    }

    void Editor::setSolution(dnai::Solution* sol)
	{
		if (m_solution == sol)
			return;
		m_solution = sol;
		emit solutionChanged(sol);
	}

	interfaces::ISolution *Editor::solution() const
    {
        return m_solution;
    }

    Solution *Editor::getSolution() const
    {
        return dynamic_cast<Solution*>(solution());
    }
}
