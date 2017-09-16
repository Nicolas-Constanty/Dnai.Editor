import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Item {
    property alias content: rectangle.contentItem
    property alias rectRef: rectangle
    ScrollView {
        id: rectangle
        anchors.rightMargin: 20
        anchors.leftMargin: 20
        anchors.bottomMargin: 20
        anchors.topMargin: 50
        anchors.fill: parent
    }
}
