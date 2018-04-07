#ifndef COREPACKAGES_REPLIES_VARIABLE_TYPESET_H
#define COREPACKAGES_REPLIES_VARIABLE_TYPESET_H

#include <string>

#include "dnai/corepackages/replies/emptyreply.h"
#include "dnai/corepackages/commands/variable/settype.h"

namespace dnai
{
    namespace corepackages
    {
        namespace variable
        {
            class TypeSet : public EmptyReply<SetType>
            {
            public:
                Declared(SetType const &cmd) :
                    EmptyReply<SetType>(cmd)
                {

                }

                virtual ~TypeSet() = default;

            public:
                static std::string EVENT()
                {
                    return "VARIABLE.TYPE_SET";
                }
            };
        }
    }
}

#endif // COREPACKAGES_REPLIES_VARIABLE_TYPESET_H

