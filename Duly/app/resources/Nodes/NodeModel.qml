import QtQuick 2.0

Item {
    property string name: "Node name"
    property string description: "This the node descrition"
    property bool flowIn: true
    property bool flowOut: true
    property string icon: ""
    property int instruction_id: -1

    property ListModel inputs
    property ListModel outputs
}
