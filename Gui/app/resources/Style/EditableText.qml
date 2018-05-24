import QtQuick 2.9
import DNAI 1.0

TextInput {
    id: control
    property string placeholderText: "Enter text here..."

    font.family: AppSettings.theme["font"]["family"]
    font.pointSize: AppSettings.theme["font"]["pixelSize"]
    horizontalAlignment: Qt.AlignHCenter
    verticalAlignment: Qt.AlignVCenter
    color: AppSettings.theme["text"]["color"]
    selectByMouse: true

    MText {
        anchors.fill: parent
        text: control.placeholderText
        font.pointSize: AppSettings.theme["font"]["pixelSize"]
        color: AppSettings.theme["text"]["disableColor"]
        font.italic: true
        visible: !control.text
    }
}
