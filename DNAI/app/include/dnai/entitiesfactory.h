#ifndef ENTITIESFACTORY_H
#define ENTITIESFACTORY_H

#include "dnai/controllers/icontroller.h"
#include "ifactory.h"
#include "qmlresources/instructionid.h"

class EntitiesFactory : public IFactory<dnai::controllers::IController, dnai::qmlresources::QInstructionID::Instruction_ID>
{
public:
	EntitiesFactory() = default;
};

#endif // ENTITIESFACTORY_H
