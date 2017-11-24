import QtQuick 2.9
import QtQuick.Controls 2.2
import Utils 1.0

ToolButton {
    id: control

    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                            contentItem.implicitWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(background ? background.implicitHeight : 0,
                             contentItem.implicitHeight + topPadding + bottomPadding)
    baselineOffset: contentItem.y + contentItem.baselineOffset

    padding: 6

    contentItem: Text {
        text: control.text
        font: control.font
        color: control.enabled ? (control.visualFocus ? DulySettings.style.text.lightColor : DulySettings.style.text.color) : DulySettings.style.text.disableColor
        elide: Text.ElideRight
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    background: Rectangle {
        implicitWidth: 40
        implicitHeight: 40

        color: Qt.darker( DulySettings.style.text.color, control.enabled && (control.checked || control.highlighted) ? 1.5 : 1.0)
        opacity: control.down ? 1.0 : control.enabled && (control.checked || control.highlighted) ? 0.5 : 0
        visible: control.down || (control.enabled && (control.checked || control.highlighted))
    }
}
