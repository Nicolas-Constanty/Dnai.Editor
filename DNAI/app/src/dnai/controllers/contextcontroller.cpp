#include "dnai/controllers/contextcontroller.h"
#include "dnai/controllers/clientcontroller.h"
#include "dnai/commands/entitydeclare.h"

namespace dnai
{
	namespace controllers
	{
        ContextController::ContextController()
            : AController<
              dnai::models::Class,
              Reply::EntityDeclared const&
              >("")
		{

		}

		QQuickItem* ContextController::createView()
		{
			return nullptr;
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

		models::IClone* ContextController::clone() const
		{
			return new ContextController();
		}

        commands::ICommand* ContextController::createCommand() const
		{
			const auto parent = dynamic_cast<dnai::models::Common *>(m_model->parent());
			if (parent)
                return new commands::EntityDeclare(PackageDataCom::ENTITYCORE::CONTEXT_D, parent->uid(), m_model->name());
            return new commands::EntityDeclare(PackageDataCom::ENTITYCORE::CONTEXT_D, -1, m_model->name());
		}
	}
}
