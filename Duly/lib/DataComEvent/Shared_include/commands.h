#ifndef COMMANDS_H
#define COMMANDS_H

#include "Scalar.h"
#include "List.h"
#include "Object.h"

#include "packagecore.h"

namespace Command {

    using Declare = Object<
        Scalar<PackageDataCom::ENTITYCORE>,
        Scalar<uint32_t>,
        Scalar<QString>,
        Scalar<PackageDataCom::VISIBILITYCORE>
    >;
}

#endif // COMMANDS_H
