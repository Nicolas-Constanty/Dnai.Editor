import QtQuick 2.0

import Dnai.Theme 1.0

Label {
    id: clickableTextId
    font.underline: true

    signal pressed()
    signal hoverEnter()
    signal hoverExit()

    MouseArea {
        id: buttonClickableMouse
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            clickableTextId.pressed()
        }
        onEntered: {
            buttonClickableMouse.cursorShape = Qt.PointingHandCursor
            clickableTextId.hoverEnter()
        }
        onExited: {
            buttonClickableMouse.cursorShape = Qt.ArrowCursor
            clickableTextId.hoverExit()
        }
    }
}
