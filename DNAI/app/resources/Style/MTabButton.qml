import QtQuick 2.0
import QtQuick.Controls 2.2

TabButton {
    id: control
    property bool closable: true
    property int iconsize: 12
    property int margin: 20
    width: text.length * font.pointSize + iconsize + margin * 2
    anchors.top: parent.top
    anchors.bottom: parent.bottom


    contentItem: Item {
        anchors.centerIn: parent
        Image {
            id: img
            width: iconsize
            height: iconsize
            anchors.right: txt.left
        }
        Text {
            id: txt
            anchors.centerIn: parent
            text: control.text
            font: control.font
            opacity: enabled ? 1.0 : 0.3
            color: checked ? "#ffffffff" : "#84FFFFFF"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }
        MouseArea {
            id: itemArea
            anchors.fill: parent
            cursorShape: Qt.OpenHandCursor
            hoverEnabled: true
        }
        FontAwesomeTextSolid {
            visible: checked || itemArea.containsMouse
            anchors.right: parent.right
            anchors.rightMargin: 5
            anchors.verticalCenter: parent.verticalCenter
            font.pointSize: 10
            text: "\uf00d"
            color: (checked) ? "#FFFFFFFF" : "#80FFFFFF"
            MouseArea {
                id: ma
                cursorShape: Qt.PointingHandCursor
                height: 14
                width: 14
            }
        }
    }
    background: Rectangle {
        color: checked ? "#16000000" : "#16FFFFFF"
    }
}
