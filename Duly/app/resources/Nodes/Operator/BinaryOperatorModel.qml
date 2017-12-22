import QtQuick 2.0
import CustomGeometry 1.0
import Utils 1.0

import "../"

NodeModel {

    flowIn: false
    flowOut: false
    inputs: ListModel {
        ListElement { t: IOType.Generic; n: "Value 1" }
        ListElement { t: IOType.Generic; n: "Value 2" }
    }

    outputs: ListModel {
        ListElement { t: IOType.Generic; n: "Result" }
    }
}
