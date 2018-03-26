#ifndef COREPACKAGES_REPLIES_DECLARATOR_REMOVED_H
#define COREPACKAGES_REPLIES_DECLARATOR_REMOVED_H

#include <string>

#include "dnai/corepackages/replies/emptyreply.h"
#include "dnai/corepackages/commands/declarator/remove.h"

namespace dnai
{
    namespace corepackages
    {
        namespace declarator
        {
            class Removed : public EmptyReply<Remove>
            {
            public:
                Removed(Remove const &cmd) :
                    EmptyReply<Remove>(cmd)
                {

                }

                virtual ~Removed() = default;

            public:
                static std::string EVENT()
                {
                    return "DECLARATOR.REMOVED";
                }
            };
        }
    }
}

#endif // COREPACKAGES_REPLIES_DECLARATOR_REMOVED_H
