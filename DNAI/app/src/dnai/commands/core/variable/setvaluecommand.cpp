#include <QJsonDocument>

#include "dnai/commands/core/variable/setvaluecommand.h"
#include "core.h"
#include "dnai/models/gui/declarable/variable.h"

namespace dnai
{
    namespace commands
    {
        namespace variable
        {
            SetValueCommand::SetValueCommand(const models::Entity &variable, const QString &value) :
                CoreCommand(
                    "Variable.SetValue",
                    true,
                    [&variable, &value]() {
                        core::variable::setValue(variable.id(), value);
                    },
                    [this, &variable]() {
                        core::variable::setValue(variable.id(), oldValue);
                    }
                ),
                oldValue(QJsonDocument(variable.guiModel<models::gui::declarable::Variable>()->value()).toJson())
            {

            }
        }
    }
}
