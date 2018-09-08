import QtQuick 2.10
import QtQuick.Controls 2.2

import DNAI 1.0
import Dnai.Settings 1.0
import Dnai.FontAwesome 1.0
import Dnai.Theme 1.0

import "../Style"

MouseArea {
    id: mouseArea
    hoverEnabled: true

    property int absX: Editor.qmlMainView().mapFromItem(mouseArea, mouseArea.mouseX, mouseArea.mouseY).x
    property int absY: Editor.qmlMainView().mapFromItem(mouseArea, mouseArea.mouseX, mouseArea.mouseY).y

    property string text: "Did you know"

    Rectangle {
        id: rectId
        visible: mouseArea.containsMouse && timerId.timerTriggered
        parent: Editor.qmlMainView()
        x: (mouseArea.absX + rectId.width + 10) > Editor.qmlMainView().width ? mouseArea.absX - (rectId.width * 1) : mouseArea.absX + 10
        y: (mouseArea.absY + rectId.height + 10) > Editor.qmlMainView().height ? mouseArea.absY - (rectId.height * 1)  : mouseArea.absY + 10
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

        Label {
            id: textId
            anchors.left: icons.right
            anchors.leftMargin: 5
            anchors.verticalCenter: rectId.verticalCenter
            text: mouseArea.text
        }
    }
}
