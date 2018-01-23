import QtQuick 2.9
import CustomGeometry 1.0
import QtQuick.Controls 2.2

import "../Style"

Item {
    id: item1
    //    property alias borderColor: rect.borderColor
    property alias refRect: rect
    property alias refText: textArea
    property alias model: list.model
    property alias delegate: list.delegate
    property string title: "Title"
    height: 50
    Rectangle {
        id: rect
        antialiasing: true
        radius: 10
        border.width: 2
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        anchors.bottomMargin: 10
        anchors.topMargin: textArea.height / 2
        anchors.fill: parent
        ListView {
            id: list
        }
        Rectangle {
            id: textArea
            width: label.width * 2
            radius: rect.radius / 2
            height: (label.font.pointSize + 2) * 2
            border.width: 2
            anchors.horizontalCenterOffset: 0
            anchors.top: parent.top
            anchors.topMargin: -(label.font.pointSize + 2)
            anchors.horizontalCenter: parent.horizontalCenter

            MLabel {
                id: label
                text: qsTr(title)
                anchors.verticalCenter: parent.verticalCenter
                font.pointSize: 8
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }
}
