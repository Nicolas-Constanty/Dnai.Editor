import QtQuick 2.0
import "../"
import DNAI.Enums 1.0

BinaryOperatorModel {

    outputs: ListModel {
        ListElement { t: IOType.Bool; n: "Result" }
    }
}
