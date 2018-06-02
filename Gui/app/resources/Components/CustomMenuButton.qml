import QtQuick 2.0

import "../Style"

import DNAI 1.0

Item {
    id: buttonItemId

    signal pressed()
    signal hoverEnter()
    signal hoverExit()
    property string textValue: ""
    property int textPointSize: 15


    Rectangle {
        id: buttonLaunch
        anchors.fill: parent
        color: AppSettings.theme["button"]["color"]

        MLabel {
            property string hoverColor: AppSettings.theme["button"]["text"]["hovercolor"]
            property string notHoverColor: AppSettings.theme["button"]["text"]["color"]

            id: buttonLaunchText
            text: buttonItemId.textValue
            color: notHoverColor
            font.pointSize: buttonItemId.textPointSize
            anchors.horizontalCenter: buttonLaunch.horizontalCenter
            anchors.verticalCenter: buttonLaunch.verticalCenter

            function enter() {
                buttonLaunch.color = AppSettings.theme["button"]["hovercolor"]
                buttonLaunchText.color = hoverColor
                buttonItemId.hoverEnter()
            }

            function exit() {
                buttonLaunch.color = AppSettings.theme["button"]["color"]
               buttonLaunchText.color = notHoverColor
                buttonItemId.hoverExit()
            }
        }

        MouseArea {
            id: buttonLaunchMouse
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                buttonItemId.pressed()
            }
            onEntered: {
                buttonLaunchMouse.cursorShape = Qt.PointingHandCursor
                buttonLaunchText.enter()
            }
            onExited: {
                buttonLaunchMouse.cursorShape = Qt.ArrowCursor
                buttonLaunchText.exit()
            }
        }
    }

}
