#ifndef CLASSCONTROLLER_H
#define CLASSCONTROLLER_H

#include "icontroller.h"
#include "dnai/models/class.h"

namespace dnai
{
	namespace controllers
	{
		class ClassController : public AController<models::Class, void>
		{
		public:
			explicit ClassController();
			explicit ClassController(const ClassController &pp) = default;

		public:
			IClone * clone() const override;
		public:
			QQuickItem * createView() override;
		protected:
			commands::ICommand* createCommand() const override;
		};
	}
}

#endif //CLASSCONTROLLER_H