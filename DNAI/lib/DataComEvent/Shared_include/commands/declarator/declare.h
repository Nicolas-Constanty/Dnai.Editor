#ifndef COMMAND_DECLARATOR_DECLARE_H
#define COMMAND_DECLARATOR_DECLARE_H

#include "Cerealizable/Tuple.hpp"
#include "packagecore.h"

using namespace PackageDataCom;
using namespace Cerealization::Cerealizable;

namespace Command
{
    namespace Declarator
    {
        class Declare : public Tuple<EntityID, ENTITY_CORE, QString, VISIBILITYCORE>
        {
        public:
            Declare(EntityID p_declarator = EntityID(), ENTITY_CORE p_type = ENTITY_CORE(), QString const &p_name = QString(), VISIBILITYCORE p_visibility = VISIBILITYCORE()) :
                Tuple<EntityID, ENTITY_CORE, QString, VISIBILITYCORE>(declarator, type, name, visibility),
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
            ENTITY_CORE type;
            QString name;
            VISIBILITYCORE visibility;
        };
    }
}

#endif // COMMAND_DECLARATOR_DECLARE_H
