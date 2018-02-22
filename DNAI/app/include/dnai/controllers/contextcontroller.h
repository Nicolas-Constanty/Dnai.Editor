#ifndef CONTEXTCONTROLLER_H
#define CONTEXTCONTROLLER_H
#include "icontroller.h"
#include "dnai/models/class.h"

namespace dnai
{
	namespace controllers
	{
		class ContextController : public IController<models::Class>
		{
		public:
			ContextController();

			QQuickItem* createView() override;

		protected:
			bool create(Reply::EntityDeclared const& reply) override;
		};

	}
}

#endif //CONTEXTCONTROLLER_H
