#ifndef COMMAND_DECLARATOR_DECLARE_H
#define COMMAND_DECLARATOR_DECLARE_H

#include <string>

#include "dnai/corepackages/commands/icommanddata.h"
#include "Cerealizable/Tuple.hpp"
#include "dnai/enums/core/core.h"

using namespace Cerealization::Cerealizable;

namespace dnai
{
    using namespace enums::core;

    namespace corepackages
    {
        namespace declarator
        {
            class Declare : public ICommandData, public Tuple<EntityID, ENTITY, QString, VISIBILITY>
            {
            public:
                Declare(EntityID p_declarator, ENTITY p_type, QString const &p_name, VISIBILITY p_visibility) :
                    Tuple<EntityID, ENTITY, QString, VISIBILITY>(declarator, type, name, visibility),
                    declarator(p_declarator),
                    type(p_type),
                    name(p_name),
                    visibility(p_visibility)
                {

                }

                ~Declare() = default;

            public:
                static std::string EVENT()
                {
                    return "DECLARATOR.DECLARE";
                }

            public:
                EntityID declarator;
                ENTITY type;
                QString name;
                VISIBILITY visibility;
            };
        }
    }
}

#endif // COMMAND_DECLARATOR_DECLARE_H
