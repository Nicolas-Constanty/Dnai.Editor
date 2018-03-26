#ifndef COREPACKAGES_REPLIES_DECLARATOR_DECLARED_H
#define COREPACKAGES_REPLIES_DECLARATOR_DECLARED_H

#include <string>

#include "dnai/corepackages/replies/reply.h"
#include "dnai/corepackages/commands/declarator/declare.h"

namespace dnai
{
    namespace corepackages
    {
        namespace declarator
        {
            class Declared : public Reply<Declare>
            {
            public:
                Declared(Declare const &cmd) :
                    Reply<Declare>(cmd)
                {

                }

                virtual ~Declared() = default;

            public:
                void fillFrom(Cerealization::Cerealizer::BinaryStream &stream) override
                {
                    stream >> declared;
                }

            public:
                static std::string EVENT()
                {
                    return "DECLARATOR.DECLARED";
                }

            public:
                EntityID declared;
            };
        }
    }
}

#endif // COREPACKAGES_REPLIES_DECLARATOR_DECLARED_H
