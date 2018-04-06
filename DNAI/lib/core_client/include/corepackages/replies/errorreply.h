#ifndef COREPACKAGES_REPLIES_ERRORREPLY_H
#define COREPACKAGES_REPLIES_ERRORREPLY_H

#include <QString>

#include "Cerealizer/Binary/Binary.hpp"
#include "dnai/corepackages/coreserialoperations.h"
#include "reply.h"

namespace dnai
{
    namespace corepackages
    {
        template <typename Cmd>
        class ErrorReply : public Reply<Cmd>
        {
        public:
            ErrorReply(Cmd const &cmd) :
                Reply<Cmd>(cmd)
            {

            }

        public:
            void fillFrom(Cerealization::Cerealizer::BinaryStream &stream) override
            {
                stream >> message;
            }

            static std::string EVENT()
            {
                return Cmd::EVENT() + ".ERROR";
            }

        public:
            QString message;
        };
    }
}

#endif // COREPACKAGES_REPLIES_ERRORREPLY_H
