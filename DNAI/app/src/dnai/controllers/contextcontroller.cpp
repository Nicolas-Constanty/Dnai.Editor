#include "dnai/controllers/contextcontroller.h"

namespace dnai
{
	namespace controllers
	{
		ContextController::ContextController() : IController<dnai::models::Class>("qrc:/resources/viewModels/Class.qml")
		{

		}

		QQuickItem* ContextController::createView()
		{
			return dynamic_cast<QQuickItem*>(App::createQmlObject(m_viewPath));
		}

		bool ContextController::create(Reply::EntityDeclared const& reply)
		{
			auto const & declare = reply.Field<Reply::COMMAND>();

			const auto model = m_model;
			m_model = new dnai::models::Class(
				static_cast<qint32>(reply.Field<Reply::RETURN>().Data()),
				declare.Field<Command::Declare::NAME>().Data(),
				model->description(),
				model->position(), model->index(), model->listIndex());
			delete model;
			addViewToCurrentContext();
			return true;
		}
	}
}