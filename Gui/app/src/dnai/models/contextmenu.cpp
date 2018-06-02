#include "dnai/models/contextmenu.h"
#include "dnai/models/entity.h"

namespace dnai
{
	namespace models
	{
		ContextMenu::ContextMenu(QObject* parent) : QObject(parent)
			, m_inputs(nullptr)
			, m_outputs(nullptr)
			, m_variables(models::gui::declarable::Variable::variables())
			, m_entitie(nullptr)
		{
		}

		gui::EntityList* ContextMenu::inputs() const
		{
			return m_inputs;
		}

		gui::EntityList* ContextMenu::outputs() const
		{
			return m_outputs;
		}

		gui::EntityList* ContextMenu::variables() const
		{
			return m_variables;
		}

		void ContextMenu::setInputs(gui::EntityList* inputs)
		{
			if (m_inputs == inputs)
				return;
			m_inputs = inputs;
			emit inputsChanged(inputs);
		}

		void ContextMenu::setOutputs(gui::EntityList* outputs)
		{
			if (m_outputs == outputs)
				return;
			m_outputs = outputs;
			emit outputsChanged(outputs);
		}

		void ContextMenu::setVariables(gui::EntityList* variables)
		{
			if (m_variables == variables)
                return;
			m_variables = variables;
			emit variablesChanged(variables);
		}

		void ContextMenu::createFromEntity(Entity* entity)
		{
			if (m_entitie == entity) return;
			m_entitie = entity;
			const auto function = entity->guiModel<gui::declarable::Function>();
			if (function)
			{
				setInputs(function->inputModels());
				setOutputs(function->outputModels());
			}
		}
	}
}
