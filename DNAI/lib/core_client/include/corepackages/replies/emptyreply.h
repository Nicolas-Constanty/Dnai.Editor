#ifndef COREPACKAGES_REPLIES_EMPTYREPLY_H
#define COREPACKAGES_REPLIES_EMPTYREPLY_H

#include "reply.h"

namespace corepackages
{
    template <typename Cmd>
    class EmptyReply : public Reply<Cmd>
    {
    public:
        EmptyReply(Cmd const &cmd) : Reply<Cmd>(cmd) {}
        virtual ~EmptyReply() = default;

    public:
        void fillFrom(Cerealization::Cerealizer::BinaryStream &) override
        {
            /* do nothing */
        }
    }
}

#endif // COREPACKAGES_REPLIES_EMPTYREPLY_H
