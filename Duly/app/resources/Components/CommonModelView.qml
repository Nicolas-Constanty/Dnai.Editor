import QtQuick 2.9
import QtQuick.Controls 2.2

import Utils 1.0


ScrollView {
    property alias listmodel: _model.model
    Component {
        id: _delegate1

        Rectangle {
            anchors.left: parent.left
            anchors.leftMargin: 15
            anchors.right: parent.right
            anchors.rightMargin: 25
            height: 100
            color: DulySettings.style.background.color
            Rectangle {
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: parent.Left
                width: parent.width * 0.025
                color: (model.item.type === 0) ? "#00897B" : (model.item.type === 1) ? "#039BE5" : (model.item.type === 2) ? "#8E24AA" : "#FB8C00"
            }
        }
    }
    ListView {
        id: _model
        anchors.fill: parent
//        model: item
        delegate: _delegate1
        spacing: 20
        clip: true
    }
}
