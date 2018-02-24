#ifndef OPENPROPERTYPANEL_H
#define OPENPROPERTYPANEL_H
#include "command.h"

namespace dnai
{
	namespace controllers
	{
		class PropertyPanel;
	}
	namespace commands
	{
		class OpenPropertyPanel : public Command
		{
		public:
			explicit OpenPropertyPanel(controllers::PropertyPanel *panel, bool save);

			void execute() const override;
			void unExcute() const override;
			void executeSave() override;

			~OpenPropertyPanel() override;
		private:
			controllers::PropertyPanel *m_panel;
			controllers::PropertyPanel *m_savedPanel;
		};
	}
}

#endif // OPENPROPERTYPANEL_H