import QtQuick 2.0
import DNAI.Enums 1.0

import "../"

LogicalNodeModel {
    name: "&&"
    description: ""
    inputs: ListModel {
        ListElement { t: IOType.Bool; n: "Value 1" }
        ListElement { t: IOType.Bool; n: "Value 2" }
    }
    instruction_id: InstructionID.AND
    menuName: "And"
}
