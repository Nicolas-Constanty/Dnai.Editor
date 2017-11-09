import QtQuick 2.0

Panel {
    id: panel
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
