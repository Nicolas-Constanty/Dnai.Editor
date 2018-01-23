import QtQuick 2.0
import QtQuick.Controls 2.2

ExpendablePanel {
    id: tr
    property alias gridview: _gridView
    title: "DragAndDrop"
    anchors.left: parent.left
    anchors.right: parent.right
    height: (parent.height - 6 * (parent.children.length -1)) / (parent.children.length)
    ScrollView
    {
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        GridView {
            id: _gridView
            anchors.fill: parent
            cellWidth: 60
            cellHeight: 60
        }
    }
}
