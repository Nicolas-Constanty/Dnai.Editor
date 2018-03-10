#include <utility>
#include "dnai/commands/corecommand.h"

namespace dnai
{
	namespace commands
	{
//        EntityDeclare::EntityDeclare(const PackageDataCom::ENTITY_CORE type, const qint32 containerId, const QString& name,
//		                             const PackageDataCom::VISIBILITYCORE visibility) : Command("ENTITY_DECLARE", true)
//		, m_type(type)
//		, m_containerID(containerId)
//		, m_name(name)
//		, m_visibility(visibility)
//		{
//		}

//		void EntityDeclare::execute() const
//		{
//			controllers::ClientController::shared().sendDeclareEvent(m_type, m_containerID, m_name, m_visibility);
//		}

//		void EntityDeclare::unExcute() const
//		{
//			controllers::ClientController::shared().sendRemoveEvent(m_type, m_containerID, m_name);
//		}

//		void EntityDeclare::executeSave()
//		{
//		}

//		EntityDeclare::~EntityDeclare() = default;

		CoreCommand::CoreCommand(std::function<void()> exec, std::function<void()> reverse):
			Command("CoreCommand"), m_exec(std::move(exec)), m_reverse(std::move(reverse))
		{
		}

		void CoreCommand::execute() const
		{
			m_exec();
		}

		void CoreCommand::unExcute() const
		{
			m_reverse();
		}

		void CoreCommand::executeSave()
		{
			execute();
		}

		CoreCommand::~CoreCommand()
		{
		}
	}
}
