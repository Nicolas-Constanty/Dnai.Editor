import QtQuick 2.0
import DNAI 1.0

TextEdit {
    id: control
    property string placeholderText: "Enter text here..."

    font.family: AppSettings.style.font.family
    font.pointSize: AppSettings.style.font.pixelSize
    horizontalAlignment: Qt.AlignHCenter
    verticalAlignment: Qt.AlignVCenter
    color: AppSettings.style.text.color
    selectByMouse: true

    MText {
        anchors.fill: parent
        text: control.placeholderText
        font.pointSize: AppSettings.style.font.pixelSize
        color: AppSettings.style.text.disableColor
        font.italic: true
        visible: !control.text
    }
}
