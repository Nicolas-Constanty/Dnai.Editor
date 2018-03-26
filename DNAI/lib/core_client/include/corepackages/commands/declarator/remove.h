#ifndef COMMAND_DECLARATOR_REMOVE_H
#define COMMAND_DECLARATOR_REMOVE_H

#include <string>
#include <QString>

#include "dnai/corepackages/commands/icommanddata.h"
#include "Cerealizable/Tuple.hpp"
#include "dnai/enums/core/core.h"

using namespace Cerealization::Cerealizable;
using namespace dnai::enums::core;

namespace dnai
{
    namespace corepackages
    {
        namespace declarator
        {
            class Remove : public ICommandData, public Tuple<EntityID, QString>
            {
            public:
                Remove(EntityID p_declarator, QString p_name) :
                    Tuple<EntityID, QString>(declarator, name),
                    declarator(p_declarator),
                    name(p_name)
                {

                }

                ~Remove() = default;

            public:
                static std::string EVENT()
                {
                    return "DECLARATOR.REMOVE";
                }

            public:
                EntityID declarator;
                QString name;
            };
        }
    }
}

#endif // COMMAND_DECLARATOR_REMOVE_H
