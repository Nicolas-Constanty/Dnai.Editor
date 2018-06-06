import QtQuick 2.0
import DNAI.Enums 1.0

import "../.."

UnaryOperatorModel {
    name: "-1"
    description: "Multiplicate by -1"
    instruction_id: InstructionID.INVERSE
    menuName: "Reverse"
}
