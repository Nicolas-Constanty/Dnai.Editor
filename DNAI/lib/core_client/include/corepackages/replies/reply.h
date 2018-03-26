#ifndef COREPACKAGES_REPLIES_REPLY_H
#define COREPACKAGES_REPLIES_REPLY_H

#include "Cerealizer/Binary/BinaryStream.hpp"

namespace dnai
{
    namespace corepackages
    {
        template <typename Cmd>
        class Reply
        {
        public:
            using Command = Cmd;

        public:
            Reply(Command const &cmd) :
                command(cmd)
            {

            }

            virtual ~Reply() = default;

        public:
            virtual void fillFrom(Cerealization::Cerealizer::BinaryStream &stream) = 0;

        public:
            Command const &command;
        };
    }
}

#endif // COREPACKAGES_REPLIES_REPLY_H
