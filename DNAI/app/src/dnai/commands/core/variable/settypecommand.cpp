#include "dnai/commands/core/variable/settypecommand.h"
#include "core.h"
#include "dnai/models/gui/declarable/variable.h"

namespace dnai
{
    namespace commands
    {
        namespace variable
        {
            SetTypeCommand::SetTypeCommand(const models::Entity &variable, const models::Entity &type) :
                CoreCommand(
                    "Variable.SetType",
                    true,
                    [&variable, &type]() {
                        core::variable::setType(variable.id(), type.id());
                    },
                    [this, &variable]() {
                        core::variable::setType(variable.id(), this->oldType);
                    }
                ),
                oldType(variable.guiModel<models::gui::declarable::Variable>()->varType())
            {

            }
        }
    }
}
