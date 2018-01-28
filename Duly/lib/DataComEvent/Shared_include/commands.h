#ifndef COMMANDS_H
#define COMMANDS_H

#include "Scalar.h"
#include "List.h"
#include "Object.h"

#include "packagecore.h"

namespace Command {

    namespace Declare {
        using Data = Object<
            Scalar<PackageDataCom::ENTITYCORE>,
            Scalar<uint32_t>,
            Scalar<QString>,
            Scalar<PackageDataCom::VISIBILITYCORE>
        >;

        enum Field
        {
            ENTITY_TYPE,
            CONTAINER_ID,
            NAME,
            VISIBILITY
        };
    }
}

#endif // COMMANDS_H
