#ifndef PROPERTYPANEL_H
#define PROPERTYPANEL_H
#include "icontroller.h"
#include "dnai/models/entity.h"

namespace dnai
{
	namespace controllers
	{
        class PropertyPanel : public AController<models::Entity, void>
		{
		public:
			explicit PropertyPanel();
			explicit PropertyPanel(const PropertyPanel &pp) = default;

		public:
			IClone* clone() const override;
		public:
            QQuickItem* createView() override;
		protected:
			commands::ICommand* createCommand() override;
		};
	}
}


#endif // PROPERTYPANEL_H
