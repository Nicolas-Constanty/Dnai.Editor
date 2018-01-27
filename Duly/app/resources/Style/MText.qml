import QtQuick 2.0
import Utils 1.0

Text {
    text: qsTr("Text")
    color: DulySettings.style.text.color
    font.family: DulySettings.style.font.family
    font.pointSize: 10
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
    renderType: Text.NativeRendering
    clip: true
}
