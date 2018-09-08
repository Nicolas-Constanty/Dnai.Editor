import QtQuick 2.0
import QtQuick.Controls 2.2

Button {
    id: control
    property alias cursorShape: mouseArea.cursorShape

    contentItem: Label {
        text: control.text
        font.underline: true
        color: "#639DBD"
    }
    background: Rectangle {
        color: "transparent"
    }

    MouseArea
    {
        id: mouseArea
        anchors.fill: parent
        onPressed:  mouse.accepted = false
    }
}
