import QtQuick 2.0
import "../"
import DNAI.Enums 1.0

NodeModel {
    property int type: 0
    description: "Get the value of a variable"
    outputs: ListModel {
        ListElement { t: IOType.Int; n: "output" }
    }
    instruction_id: InstructionID.GETTER
    onModelChanged: {
        if (model !== null) {

            if (model.linked === null || model.linked.length < 1)
                console.error('In getter, model.linked must contain exactly one element, the name of the variable linked')
            else
            {
                var names = model.linked[0].split('.');
                name = names[names.length - 1]
            }
        }
    }
}
