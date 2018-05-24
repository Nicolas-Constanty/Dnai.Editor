import QtQuick 2.0


Text {
    property alias mousearea: ma
    id: ct
    text: but.text
    font.underline: true
    color: "#639DBD"
    MouseArea {
        id: ma
        cursorShape: Qt.PointingHandCursor
        anchors.fill: parent
    }
}
