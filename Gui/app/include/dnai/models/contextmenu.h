#ifndef DNAI_MODELS_CONTEXT_MENU_H
#define DNAI_MODELS_CONTEXT_MENU_H

#include <QObject>
#include "dnai/models/gui/entitylist.h"

namespace dnai
{
	namespace models
	{
		class ContextMenu : public QObject
		{
			Q_OBJECT
			Q_PROPERTY(dnai::models::gui::EntityList *inputs READ inputs WRITE setInputs NOTIFY inputsChanged)
			Q_PROPERTY(dnai::models::gui::EntityList *outputs READ outputs WRITE setOutputs NOTIFY outputsChanged)
			Q_PROPERTY(dnai::models::gui::EntityList *variables READ variables WRITE setVariables NOTIFY variablesChanged)

		public:
			explicit ContextMenu(QObject *parent = nullptr);
			gui::EntityList * inputs() const;
			gui::EntityList * outputs() const;
			gui::EntityList * variables() const;

			void setInputs(gui::EntityList *inputs);
			void setOutputs(gui::EntityList *outputs);
			void setVariables(gui::EntityList *variables);
			
		signals:
			void inputsChanged(gui::EntityList *inputs);
			void outputsChanged(gui::EntityList *outputs);
			void variablesChanged(gui::EntityList *variables);

		public:
			void createFromEntity(Entity *entity);

		private:
			gui::EntityList *m_inputs;
			gui::EntityList *m_outputs;
			gui::EntityList *m_variables;
			Entity* m_entitie;
		};
	}
}

#endif //DNAI_MODELS_CONTEXT_MENU_H