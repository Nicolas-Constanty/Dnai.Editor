import QtQuick 2.0

import "../Style"

import DNAI 1.0
import Dnai.FontAwesome 1.0
import Dnai.Settings 1.0

Item {
    id: mainItem
    property Modal popup
    property var buttonModel

    property int widthValue: container.childrenRect.width + 40
    property int heightValue: container.childrenRect.height + 40
    property var orientation: ListView.Horizontal

    height: heightValue
    width: widthValue

    signal pressedYes()
    signal pressedNo()

    Component.onCompleted: {
        console.log("-------------------- " + heightValue)
    }

    property string title: ""
    property string description: ""
    property string icon: ""
    property string iconColor: AppSettings.theme["colors"]["accent"]["yellow"]

    TextAwesomeSolid {
        id: crossId
        text: "\uf00d"
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.topMargin: 10
        anchors.rightMargin: 10
        color: AppSettings.theme["text"]["color"]

        MouseArea {
            id: crossMouseId
            anchors.fill: crossId
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor

            onReleased: {
                mainItem.popup.close()
            }

        }
    }

    Item {
        id: container
        anchors.fill: parent

        anchors.margins: 20

        MLabel {
            id: titleId
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            font.pointSize: 16

            text: mainItem.title
        }

        TextAwesomeSolid {
            text: mainItem.icon
            anchors.verticalCenter: titleId.verticalCenter
            anchors.right: titleId.left
            anchors.rightMargin: 5
            font.pointSize: 17
            color: iconColor
        }

        MLabel {
            id: descId
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: titleId.bottom
            anchors.topMargin: 5
            text: mainItem.description
            font.pointSize: 15
        }

        Row {
            anchors.top: descId.bottom
            anchors.topMargin: 20
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 20

            Repeater {
                model: mainItem.buttonModel

                delegate: CustomMenuButton {
                    id: refButton
                    width: refButton.textWidth + 20
                    height: refButton.textHeight + 20
                    textValue: modelData.text
                    hoverColor: modelData.hoverColor
                    notHoverColor: modelData.notHoverColor
                    colorRect: modelData.colorRect
                    hoverColorRect: modelData.hoverColorRect

                    onPressed: {
                        modelData.itemAnswer.callback()
                    }
                }
        }
        }
    }
}
