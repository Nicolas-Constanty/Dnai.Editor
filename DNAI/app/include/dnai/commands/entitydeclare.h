#ifndef ENTITYDECLARE_H
#define ENTITYDECLARE_H
#include "command.h"
#include "dnai/controllers/clientcontroller.h"

namespace dnai
{
	namespace commands
	{
		class EntityDeclare : public Command
		{
		public:
			EntityDeclare(PackageDataCom::ENTITYCORE type, qint32 containerID, const QString &name, PackageDataCom::VISIBILITYCORE visibility = PackageDataCom::VISIBILITYCORE::PUBLIC);
			void execute() const override;
			void unExcute() const override;
			void executeSave() override;
			~EntityDeclare() override;

		private:
			PackageDataCom::ENTITYCORE m_type;
			qint32 m_containerID;
			QString m_name;
			PackageDataCom::VISIBILITYCORE m_visibility;
		};
	}
}

#endif //ENTITYDECLARE_H