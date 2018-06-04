import QtQuick 2.9
import DNAI 1.0
import Dnai.FontAwesome 1.0

//f106
//TODO ajouter error
TextInput {
    id: control
    property string placeholderText: "Enter text here..."
    property string selectColor: AppSettings.theme["editableText"]["color"]["border"]["select"]
    property string deselectColor: AppSettings.theme["editableText"]["color"]["border"]["deselect"]
    property string selectColorBackground: AppSettings.theme["editableText"]["color"]["background"]["select"]
    property string deselectColorBackground: AppSettings.theme["editableText"]["color"]["background"]["deselect"]

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
        anchors.right: parent.right
        anchors.rightMargin: parent.rightPadding
        anchors.leftMargin: parent.leftPadding
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        text: control.placeholderText
        font.pointSize: AppSettings.theme["font"]["pixelSize"]
        color: AppSettings.theme["text"]["disableColor"]
        font.italic: true
        visible: !control.text
        horizontalAlignment: parent.horizontalAlignment
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

    /*TextAwesomeSolid {
        id: crossId
        text: "\uf106"
        anchors.top: control.bottom
        anchors.topMargin: 3
        anchors.left: control.left
     //   anchors.leftMargin: 10
        color: AppSettings.theme["text"]["color"]
    }*/
}
