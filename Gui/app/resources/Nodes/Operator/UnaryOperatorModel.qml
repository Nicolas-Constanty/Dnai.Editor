import QtQuick 2.0
import "../"
import DNAI.Enums 1.0

NodeModel {

    inputs: ListModel {
        ListElement { t: IOType.Generic; n: "Value 1" }
    }

    outputs: ListModel {
        ListElement { t: IOType.Generic; n: "Result" }
    }
}
