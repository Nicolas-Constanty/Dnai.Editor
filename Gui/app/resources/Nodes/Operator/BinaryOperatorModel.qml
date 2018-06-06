import QtQuick 2.0
import DNAI.Enums 1.0

import "../"

NodeModel {

    inputs: ListModel {
        ListElement { t: IOType.Generic; n: "Value 1" }
        ListElement { t: IOType.Generic; n: "Value 2" }
    }

    outputs: ListModel {
        ListElement { t: IOType.Generic; n: "Result" }
    }
}
