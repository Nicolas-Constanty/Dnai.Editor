import QtQuick 2.0
import "../"
import Utils 1.0

NodeModel {

    flowIn: false
    flowOut: false
    inputs: ListModel {
        ListElement { t: IOType.Generic; n: "Value 1" }
    }

    outputs: ListModel {
        ListElement { t: IOType.Generic; n: "Result" }
    }
}
