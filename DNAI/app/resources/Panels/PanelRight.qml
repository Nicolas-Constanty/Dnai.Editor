import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQml.Models 2.1

import DNAI 1.0

import "../Components"
import "../Panels"
import "../Style"

Panel {
    id: panel
    Column {
        id: _col
        spacing: 6
        anchors.left: panel.left
        anchors.leftMargin: 6
        anchors.right: panel.right
        anchors.rightMargin: 6
        anchors.top: panel.top
        anchors.topMargin: 6
        anchors.bottom: panel.bottom
        anchors.bottomMargin: 6

        DragAndDropPanel {
            anchors.left: parent.left
            anchors.right: parent.right
            height: (parent.height - 6 * (parent.children.length -1)) / (parent.children.length)
        }

        Properties {
            anchors.left: parent.left
            anchors.right: parent.right
            height: (parent.height - 6 * (parent.children.length -1)) / (parent.children.length)
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
