#ifndef COREPACKAGES_REPLIES_VARIABLE_VALUESET_H
#define COREPACKAGES_REPLIES_VARIABLE_VALUESET_H

#include <string>

#include "dnai/corepackages/replies/emptyreply.h"
#include "dnai/corepackages/commands/variable/setvalue.h"

namespace dnai
{
    namespace corepackages
    {
        namespace variable
        {
            class ValueSet : public EmptyReply<SetValue>
            {
            public:
                Declared(SetValue const &cmd) :
                    EmptyReply<SetValue>(cmd)
                {

                }

                virtual ~ValueSet() = default;

            public:
                static std::string EVENT()
                {
                    return "VARIABLE.VALUE_SET";
                }
            };
        }
    }
}

#endif // COREPACKAGES_REPLIES_VARIABLE_VALUESET_H

