import QtQuick 2.9
import DNAI 1.0

TextInput {
    id: control
    property string placeholderText: "Enter text here..."
    property string selectColor: "#847AFF"
    property string deselectColor: "#4E4E5E"
    property string selectColorBackground: "#333232"
    property string deselectColorBackground: "#252526"

    font.family: AppSettings.theme["font"]["family"]
    font.pointSize: AppSettings.theme["font"]["pixelSize"]
    horizontalAlignment: Qt.AlignHCenter
    verticalAlignment: Qt.AlignVCenter
    color: AppSettings.theme["text"]["color"]
    selectByMouse: true
    clip: true
    leftPadding: 5
    rightPadding: 5


    Rectangle {
        anchors.fill: parent
        color: control.focus == true ? selectColorBackground : deselectColorBackground
        z: parent.z - 1
    }

  //  mouseSelectionMode: TextInput.SelectCharacters

    MouseArea {
        id: controlMouseId
        anchors.fill: control
       // hoverEnabled: true
        cursorShape: Qt.IBeamCursor

        onPressed: {
            control.focus = true
            control.cursorPosition = control.positionAt(controlMouseId.mouseX, controlMouseId.mouseY)
        }

    }

    MText {
        anchors.fill: parent
        text: control.placeholderText
        font.pointSize: AppSettings.theme["font"]["pixelSize"]
        color: AppSettings.theme["text"]["disableColor"]
        font.italic: true
        visible: !control.text
    }

    Rectangle {
        id: editableRectId
        anchors.top: control.bottom
        anchors.topMargin: -3
        anchors.left: control.left
        anchors.right: control.right
        height: 3
        color: control.focus == true ? selectColor : deselectColor
    }
}
