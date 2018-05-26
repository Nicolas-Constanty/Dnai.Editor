import QtQuick 2.0
import QtQuick.Controls 2.2
import Dnai.Controls 1.0

PanelView {
    id: _panel
    property var model: null
    property real contentHeight: 24
    property real valueSpacing: 5
    property ButtonAwesomeSolid createButton: _createButton

    anchors.left: parent.left
    anchors.right: parent.right
    height: _createButton.height + _values.height + _panel.content.anchors.topMargin * 2 + header.height - _panel.valueSpacing + _panel.spacing * 2
    header.title.text: qsTr("Enumeration Values")

    Item {
        id: _values
        anchors.left: parent.left
        anchors.right: parent.right
        height: (_panel.contentHeight + _panel.valueSpacing) * model.count

        Column {
            anchors.left: parent.left
            anchors.right: parent.right
            spacing: _panel.valueSpacing
            Repeater {
                model: _panel.model
                EnumValue {
                    height: _panel.contentHeight
                    width: _values.width
                }
            }
        }
    }
    ButtonAwesomeSolid {
        id: _createButton
        label.text: "\uf055"
        anchors.horizontalCenter: parent.horizontalCenter
        label.font.pointSize: 30
        height: 40
        width: 40
        color: "#ffffff"
        background: Rectangle {
            color: "transparent"
        }
    }
}
