import QtQuick 2.0

Item {
    property string name: "Node name"
    property string description: "This is the node description"
    property string menuName: "default menu name"
    property bool flowIn: true
    property bool flowOut: true
    property string icon: ""
    property int instruction_id: -1
    property var model: null

    property ListModel inputs
    property ListModel outputs
}
