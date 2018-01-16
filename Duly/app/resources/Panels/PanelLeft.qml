import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import Utils 1.0

import "../Panels"

Panel {
    id: panel
    property alias treeview: tr
    TreeView {

        function changeCurrent(cur)
        {
            console.log(cur)
            tr.selection.select(cur)
            Manager.selectTreeItem(cur)
        }

        id: tr
        height: panel.height / 2 - anchors.topMargin
        anchors.left: panel.left
        anchors.leftMargin: 10
        anchors.right: panel.right
        anchors.rightMargin: 10
        anchors.top: panel.top
        anchors.topMargin: 30
        model: Manager.projectModel
        TableViewColumn {
            title: "Project"
            role: "display"
        }
        style: TreeViewStyle {
            alternateBackgroundColor : DulySettings.style.alternateBackground
            backgroundColor : DulySettings.style.background
            highlightedTextColor : DulySettings.style.text.accentColor
            textColor : DulySettings.style.text.color
        }
        onClicked: {
            Manager.updateNamespace(index)
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
