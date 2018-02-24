#ifndef CONTEXTCONTROLLER_H
#define CONTEXTCONTROLLER_H
#include "icontroller.h"
#include "dnai/models/class.h"

namespace dnai
{
	namespace controllers
	{
        class ContextController : public AController<models::Class>
		{
		public:
			ContextController();

			QQuickItem* createView() override;

		protected:
			bool create(Reply::EntityDeclared const& reply) override;
        private:
	        IClone* clone() const override;
        protected:
	        commands::ICommand* createCommand() override;
		};

	}
}

#endif //CONTEXTCONTROLLER_H
