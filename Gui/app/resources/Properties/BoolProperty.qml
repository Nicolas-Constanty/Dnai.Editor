import QtQuick 2.0
import QtQuick.Controls 2.2

import Dnai.Controls 1.0

PanelView {
    id: _panel
    property alias value: _value.checked
    property alias label: _value.text
    property string name: "Bool property"
    property real contentHeight: 24

    anchors.left: parent.left
    anchors.right: parent.right
    height: _property.height + header.height + _panel.content.anchors.topMargin * 2

    header.title.text: name
    Item {
        id: _property
        height: _value.height
        anchors.left: parent.left
        anchors.right: parent.right
        Label {
            id: _labelOff
            height: _property.height
            text: qsTr("OFF")
            anchors.right: _value.left
            anchors.rightMargin: 5
            verticalAlignment: Text.AlignVCenter
            color:  _value.checked ? "#80000000" : "#ffffff"
        }
        Switch {
            id: _value
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Label {
            id: _labelOn
            height: _property.height
            text: qsTr("ON")
            anchors.left: _value.right
            anchors.leftMargin: 5
            verticalAlignment: Text.AlignVCenter
            color: _value.checked ? "#ffffff" : "#80000000"
        }
    }

}
