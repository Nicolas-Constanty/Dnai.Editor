#ifndef REPLIES_H
#define REPLIES_H

#include "commands.h"

namespace Reply {

    enum Field
    {
        COMMAND = 0,
        RETURN = 1
    };

    using EntityDeclared = Object<
        Command::Declare::Data,
        Scalar<uint32_t>
    >;

}

#endif // REPLIES_H
