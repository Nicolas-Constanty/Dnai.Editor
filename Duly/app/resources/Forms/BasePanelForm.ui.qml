import QtQuick 2.9
import QtQuick.Controls 2.2

Item {
    id: _control
    default property alias _contentChildren: _content.data
    property real padding: 20
    property alias spacing: _content.spacing
    property alias content: _content
    property real topPadding: -1
    property real rightPadding: -1
    property real bottomPadding: -1
    property real leftPadding: -1

    Item {
        id: _contentItem
        anchors.fill: parent
        anchors.topMargin: topPadding == -1 ? padding : topPadding
        anchors.bottomMargin: bottomPadding == -1 ? padding : bottomPadding
        anchors.leftMargin: leftPadding == -1 ? padding : leftPadding
        anchors.rightMargin: rightPadding == -1 ? padding - 5 : rightPadding
        ScrollView {
            anchors.fill: parent
            clip: true
            Column {
                id: _content
                width: _contentItem.width - 15
            }
        }
    }
}
