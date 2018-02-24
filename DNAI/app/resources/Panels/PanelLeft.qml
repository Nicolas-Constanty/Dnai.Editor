import QtQuick 2.0
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

        TreeViewPanel {
            id: tr
            title: qsTr("Solution Explorer")
            anchors.left: parent.left
            anchors.right: parent.right
            height: (parent.height - 6 * (parent.children.length -1)) / (parent.children.length)
            Component.onCompleted: {
                Manager.views.registerTreeView(tr.treeview)
            }
        }

        ExpendablePanel {
            title: "Test title"
            anchors.left: parent.left
            anchors.right: parent.right
            height: (parent.height - 6 * (parent.children.length -1)) / (parent.children.length)
        }
    }

    states: [
        State{
            name: "Visible"
            PropertyChanges{ target: panel; anchors.leftMargin: 0 }
            PropertyChanges{ target: panel; visible: true }
        },
        State{
            name:"Invisible"
            PropertyChanges{ target: panel; anchors.leftMargin: - width }
            PropertyChanges{ target: panel; visible: false }
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
                       property: "anchors.leftMargin"
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
                       property: "anchors.leftMargin"
                       duration: 500
                       easing.type: Easing.InOutQuad
                   }
                }
            }
        ]
}
