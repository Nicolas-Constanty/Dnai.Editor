import QtQuick 2.9
import QtQuick.Controls 2.2
import DNAI 1.0

import "../Style"

ToolButton {
    id: control

    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                            contentItem.implicitWidth + leftPadding + rightPadding)
    implicitHeight: 40

    contentItem: Title3 {
        text: control.text
        color: control.enabled ? (control.visualFocus ? AppSettings.style.text.lightColor : AppSettings.style.text.color) : AppSettings.style.text.disableColor
        elide: Text.ElideRight
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    background: Rectangle {
        implicitWidth: 40
        implicitHeight: 40

        color: Qt.darker( AppSettings.style.text.color, control.enabled && (control.checked || control.highlighted) ? 1.5 : 1.0)
        opacity: control.down ? 1.0 : control.enabled && (control.checked || control.highlighted) ? 0.5 : 0
        visible: control.down || (control.enabled && (control.checked || control.highlighted))
    }
}
