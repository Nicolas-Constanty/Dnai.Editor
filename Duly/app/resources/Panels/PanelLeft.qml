import QtQuick 2.0
import QtQuick.Controls 1.4
import "../Panels"
import Utils 1.0

Panel {
    id: panel
//    TreeView {
//        model: Manager.projectModel
//    }
    states: [
        State{
            name: "Visible"
            PropertyChanges{target: panel; anchors.leftMargin: 0 }
            PropertyChanges{target: panel; visible: true}
        },
        State{
            name:"Invisible"
            PropertyChanges{target: panel; anchors.leftMargin: - width }
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
