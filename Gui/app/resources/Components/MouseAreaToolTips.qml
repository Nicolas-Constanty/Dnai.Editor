import QtQuick 2.10

import DNAI 1.0
import Dnai.Settings 1.0
import Dnai.FontAwesome 1.0

import "../Style"

MouseArea {
    id: mouseArea
    hoverEnabled: true

    property int absX: mapToGlobal(mouseArea.mouseX + mouseArea.x, mouseArea.mouseY).x
    property int absY: mapToGlobal(mouseArea.mouseX + mouseArea.x, mouseArea.mouseY).y

    property string text: "Did you know"

    Rectangle {
        id: rectId
        visible: mouseArea.containsMouse && timerId.timerTriggered
        parent: Editor.qmlMainView()
        x: (mouseArea.absX + rectId.width) > Editor.qmlMainView().width ? mouseArea.absX - (rectId.width * 1) : mouseArea.absX
        y: (mouseArea.absY + rectId.height) > Editor.qmlMainView().height ? mouseArea.absY - (rectId.height * 2) - 20 : mouseArea.absY - 20
        z: Editor.qmlMainView().z + 1
        height: textId.height + 20
        width: textId.width + 20 + icons.width
        opacity: (mouseArea.containsMouse  && timerId.timerTriggered) == true ? 1.0 : 0

        color: AppSettings.theme["colors"]["accent"]["blue"]

        Behavior on opacity {
            NumberAnimation { duration: 200 }
        }

        Timer {
            id: timerId
            property bool timerTriggered: false

            running: mouseArea.containsMouse
            onRunningChanged: {
                if (running) {
                    timerTriggered = false
                }
            }

            interval: 500
            onTriggered: {
                timerTriggered = true
            }
        }

        TextAwesomeSolid {
            id: icons
            text: "\uf0eb"
            font.pointSize: 20
            anchors.left: rectId.left
            anchors.leftMargin: 5
            anchors.verticalCenter: rectId.verticalCenter
            color: AppSettings.theme["colors"]["background"]["color5"]
        }

        MText {
            id: textId
            anchors.left: icons.right
            anchors.leftMargin: 5
            anchors.verticalCenter: rectId.verticalCenter
            text: mouseArea.text
        }
    }
}
