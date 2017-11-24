import QtQuick 2.0
import QtQml.Models 2.1

Panel {
    id: panel
    property alias dragAndDropPanel: gridView

    Rectangle {
        id: containerDrag
        height: panel.height / 2 - anchors.topMargin
        anchors.left: panel.left
        anchors.leftMargin: 10
        anchors.right: panel.right
        anchors.rightMargin: 10
        anchors.top: panel.top
        anchors.topMargin: 30
        color: "#40000000"
        radius: 5
        border.color: "#EEEEEE"
        border.width: 1

        GridView {
            id: gridView
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            cellWidth: 60
            cellHeight: 60
        }
    }

    states: [
        State{
            name: "Visible"
            PropertyChanges{target: panel; anchors.rightMargin: 0 }
            PropertyChanges{target: panel; visible: true}
        },
        State{
            name:"Invisible"
            PropertyChanges{target: panel; anchors.rightMargin: - width }
            PropertyChanges{target: panel; visible: false}
        }
    ]
    state: "Visible"
    transitions: [
            Transition {
                from: "Visible"
                to: "Invisible"

                SequentialAnimation{
                   NumberAnimation {
                       target: panel
                       property: "anchors.rightMargin"
                       duration: 500
                       easing.type: Easing.InOutQuad
                   }
                   NumberAnimation {
                       target: panel
                       property: "visible"
                       duration: 0
                   }
                }
            },
            Transition {
                from: "Invisible"
                to: "Visible"
                SequentialAnimation{
                   NumberAnimation {
                       target: panel
                       property: "visible"
                       duration: 0
                   }
                   NumberAnimation {
                       target: panel
                       property: "anchors.rightMargin"
                       duration: 500
                       easing.type: Easing.InOutQuad
                   }
                }
            }
        ]
}
