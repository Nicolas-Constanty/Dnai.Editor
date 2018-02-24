#include "dnai/commands/entitydeclare.h"

namespace dnai
{
	namespace commands
	{
		EntityDeclare::EntityDeclare(const PackageDataCom::ENTITYCORE type, const qint32 containerId, const QString& name,
		                             const PackageDataCom::VISIBILITYCORE visibility) : Command("ENTITY_DECLARE", true)
		, m_type(type)
		, m_containerID(containerId)
		, m_name(name)
		, m_visibility(visibility)
		{
		}

		void EntityDeclare::execute() const
		{
			controllers::ClientController::shared().sendDeclareEvent(m_type, m_containerID, m_name, m_visibility);
		}

		void EntityDeclare::unExcute() const
		{
			controllers::ClientController::shared().sendRemoveEvent(m_type, m_containerID, m_name);
		}

		void EntityDeclare::executeSave()
		{
		}

		EntityDeclare::~EntityDeclare() = default;
	}
}
