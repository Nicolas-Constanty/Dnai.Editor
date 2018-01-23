import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQml.Models 2.3
import Utils 1.0

import "../Style"

Item {
    id: item

    signal trigger()
    width: 64; height: 64
    property alias drag: mouseArea
    property string name: "Name"
    property string description: "Description"

    property real xPos: 0
    property real yPos: 0

    property real radius: 10
    property string color: "#03A9F4"

    property string borderColor: "#81D4FA"
    property int borderWidth: 2

    x: xPos
    y: yPos

    MouseArea {
        id: mouseArea
        property real offsetX: 0
        property real offsetY: 0

        width: item.width; height: item.height
        anchors.centerIn: parent

        drag.target: tile

        onReleased: {
            item.x = mouse.x + parent.x - mouseArea.offsetX
            item.y = mouse.y + parent.y - mouseArea.offsetY
        }

        onPressed:  {
            mouseArea.offsetX = mouse.x
            mouseArea.offsetY = mouse.y
        }

        Rectangle {
            height:  item.height
            width:  item.width
            radius: item.radius
            border.color: item.borderColor
            border.width: item.borderWidth
            color: item.color
            id: tile

            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter

            Drag.active: mouseArea.drag.active
            Drag.hotSpot.x: 25
            Drag.hotSpot.y: 25
            MLabel {
                id: label
                text: qsTr(item.name)
                anchors.centerIn: parent
            }
            states: State {
                when: mouseArea.drag.active
                ParentChange { target: tile; parent: item }
                AnchorChanges { target: tile; anchors.verticalCenter: undefined; anchors.horizontalCenter: undefined }
            }
        }
    }
}
