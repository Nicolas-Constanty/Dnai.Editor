import QtQuick 2.0

Component {
    MouseArea {
        id: delegateRoot

        width: 60; height: 60
        drag.target: icon

        Rectangle {
            id: icon
            width: 50; height: 50
            anchors {
                horizontalCenter: parent.horizontalCenter;
                verticalCenter: parent.verticalCenter
            }
            color: model.color
            radius: 3

            Drag.active: delegateRoot.drag.active
            Drag.source: delegateRoot
            Drag.hotSpot.x: 25
            Drag.hotSpot.y: 25

            states: [
                State {
                    when: icon.Drag.active
                    ParentChange {
                        target: icon
                    }

                    AnchorChanges {
                        target: icon;
                        anchors.horizontalCenter: undefined;
                        anchors.verticalCenter: undefined
                    }
                }
            ]
        }
    }
}
