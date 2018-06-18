import QtQuick 2.0
import DNAI 1.0

MText {
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
