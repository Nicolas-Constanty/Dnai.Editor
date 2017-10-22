import QtQuick 2.0
import "../"
import CustomGeometry 1.0

BinaryOperatorModel {

    outputs: ListModel {
        ListElement { t: IOType.Bool; n: "Result" }
    }
}
