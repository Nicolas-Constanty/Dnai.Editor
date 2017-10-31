import QtQuick 2.0
import "../"
import CustomGeometry 1.0

LogicalNodeModel {
    name: "||"
    description: ""
    inputs: ListModel {
        ListElement { t: IOType.Bool; n: "Value 1" }
        ListElement { t: IOType.Bool; n: "Value 2" }
    }
}
