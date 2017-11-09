import QtQuick 2.0
import "../"
import CustomGeometry 1.0

NodeModel {

    flowIn: false
    flowOut: false
    inputs: ListModel {
        ListElement { t: IOType.Generic; n: "Value 1" }
        ListElement { t: IOType.Generic; n: "Value 1" }
    }

    outputs: ListModel {
        ListElement { t: IOType.Generic; n: "Result" }
    }
}
