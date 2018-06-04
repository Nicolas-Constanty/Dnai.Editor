import QtQuick 2.9
import QtQuick.Controls 2.2
import DNAI 1.0

import "../Style"

ToolButton {
    id: control

    signal buttonPressed()

    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                            contentItem.implicitWidth + leftPadding + rightPadding)
    implicitHeight: 40

    contentItem: Title3 {
        text: control.text
        color: control.enabled ? (control.visualFocus ? AppSettings.theme["text"]["lightColor"] : AppSettings.theme["text"]["color"]) : AppSettings.theme["text"]["disableColor"]
        elide: Text.ElideRight
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor

        onEntered: {
            backgroundId.color = Qt.darker( AppSettings.theme["text"]["color"], 1.5)
            backgroundId.visible = true

        }

        onPressed: {
            buttonPressed()
        }

        onExited: {
            backgroundId.visible = false
        }
    }

    background: Rectangle {
        id: backgroundId
        implicitWidth: 40
        implicitHeight: 40

        color: Qt.darker( AppSettings.theme["text"]["color"], control.enabled && (control.checked || control.highlighted) ? 1.5 : 1.0)
        opacity: 0.3//control.down ? 1.0 : control.enabled && (control.checked || control.highlighted) ? 0.5 : 0
        visible: control.down || (control.enabled && (control.checked || control.highlighted))


    }
}
