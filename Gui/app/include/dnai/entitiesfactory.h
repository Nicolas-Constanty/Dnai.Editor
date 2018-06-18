#ifndef DNAI_ENTITIESFACTORY_H
#define DNAI_ENTITIESFACTORY_H

#include "dnai/interfaces/icontroller.h"
#include "dnai/interfaces/ifactory.h"
#include "enums/core/instructionid.h"

namespace dnai {
    class EntitiesFactory : public interfaces::IFactory<dnai::interfaces::IController, dnai::enums::QInstructionID::Instruction_ID>
    {
    public:
        EntitiesFactory() = default;
    };
}

#endif // DNAI_ENTITIESFACTORY_H
