import QtQuick 2.9

import DNAI 1.0
import Dnai.Settings 1.0
import Dnai.FontAwesome 1.0

TextInput {
    id: control
    property string placeholderText: "Enter text here..."
    property string selectColor: AppSettings.theme["editableText"]["color"]["border"]["select"]
    property string deselectColor: AppSettings.theme["editableText"]["color"]["border"]["deselect"]
    property string selectColorBackground: AppSettings.theme["editableText"]["color"]["background"]["select"]
    property string deselectColorBackground: AppSettings.theme["editableText"]["color"]["background"]["deselect"]
    property string errorText: ""
    property alias grparent: control.parent
    property bool canEdit: true
    property bool enableBar: true

    font.family: AppSettings.theme["font"]["family"]
    font.pointSize: AppSettings.theme["font"]["pixelSize"]
    horizontalAlignment: Qt.AlignHCenter
    verticalAlignment: Qt.AlignVCenter
    color: AppSettings.theme["text"]["color"]
    selectByMouse: true
    clip: true
    leftPadding: 5
    rightPadding: 5

    onFocusChanged: {
        if (!focus && errorId.text) {
            errorText = ""
        }
    }


    Rectangle {
        anchors.fill: parent
        color: control.focus == true ? selectColorBackground : deselectColorBackground
        z: parent.z - 1
    }

    MouseArea {
        id: controlMouseId
        anchors.fill: control
        cursorShape: canEdit ? Qt.IBeamCursor : Qt.ArrowCursor

        onPressed: {
            if (canEdit) {
                control.focus = true
                control.cursorPosition = control.positionAt(controlMouseId.mouseX, controlMouseId.mouseY)
            }
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
        visible: enableBar
        color:  (errorId.text) ? AppSettings.theme["text"]["errorColor"] : control.focus == true ? selectColor : deselectColor
    }

    MText {
        id: errorId
        parent: grparent
        text: errorText
        font.pointSize: 8
        anchors.top: control.bottom
        anchors.topMargin: 2
        anchors.rightMargin: 5
        anchors.right: control.right
        color: AppSettings.theme["text"]["errorColor"]
        z: parent.z + 1
    }

    /*TextAwesomeSolid {
        id: arrowId
        text: "\uf106"
        parent: grparent
        anchors.top: control.bottom
//        anchors.topMargin: 3
        anchors.right: control.right
        anchors.rightMargin: 5
        color: AppSettings.theme["text"]["errorColor"]
    }*/
}
