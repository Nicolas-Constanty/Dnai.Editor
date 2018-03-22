import QtQuick 2.0
import DNAI 1.0

Text {
    text: qsTr("Text")
    color: AppSettings.style.text.color
    font.family: AppSettings.style.font.family
    font.pointSize: 10
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
    renderType: Text.NativeRendering
    clip: true
}
