import QtQuick 2.0
import DNAI 1.0

TextEdit {
    id: control
    property string placeholderText: "Enter text here..."

    font.family: DulySettings.style.font.family
    font.pointSize: DulySettings.style.font.pixelSize
    horizontalAlignment: Qt.AlignHCenter
    verticalAlignment: Qt.AlignVCenter
    color: DulySettings.style.text.color
    selectByMouse: true

    MText {
        anchors.fill: parent
        text: control.placeholderText
        font.pointSize: DulySettings.style.font.pixelSize
        color: DulySettings.style.text.disableColor
        font.italic: true
        visible: !control.text
    }
}
