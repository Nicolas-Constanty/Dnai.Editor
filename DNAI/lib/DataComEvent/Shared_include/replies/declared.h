#ifndef COMMAND_DECLARATOR_DECLARED_H
#define COMMAND_DECLARATOR_DECLARED_H

#include "Cerealizable/Scalar.hpp"
#include "packagecore.h"
#include "commands/declarator/declare.h"

namespace Reply
{
    namespace Declarator
    {
        class Declared : public Scalar<PackageDataCom::EntityID>
        {
        public:
            Declared(PackageDataCom::EntityID p_id = PackageDataCom::EntityID()) :
                Scalar<PackageDataCom::EntityID>(id),
                id(p_id)
            {

            }

        public:
            static std::string EVENT()
            {
                return "DECLARATOR.DECLARED";
            }

        public:
            Command::Declarator::Declare command;
            PackageDataCom::EntityID id;
        };
    }
}

#endif // COMMAND_DECLARATOR_DECLARED_H
