import QtQuick 2.0
import CustomGeometry 1.0


Item {
    property string name: "Node name"
    property string description: "This the node descrition"
    property bool flowIn: true
    property bool flowOut: true

    property ListModel inputs
    property ListModel outputs
}
