import QtQuick 2.0
import CustomGeometry 1.0


NodeModel {

    name: "Add"
    description: "Add input 1 with input 2 and output res"
    flowIn: true
    flowOut: false

    inputs: ListModel {
        ListElement { t: IOType.Int; n: "Value 1" }
        ListElement { t: IOType.Int; n: "Value 2" }
    }

    outputs: ListModel {
        ListElement { t: IOType.Int; n: "Result" }
    }
}
