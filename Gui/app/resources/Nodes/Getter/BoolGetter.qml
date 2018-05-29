import QtQuick 2.0
import "../"
import DNAI.Enums 1.0

NodeModel {
    property var model: null
    property int type: 0
    flowIn: false
    outputs: ListModel {
        ListElement { t: IOType.Bool; n: "output" }
    }
}
