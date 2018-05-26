import QtQuick 2.0
import QtQuick.Controls 2.2
import Dnai.Controls 1.0

PanelView {
    id: _panel
    property string name: "Enum Property"
    property var model: null
    property real contentHeight: 35
    property alias label: _label
    property alias value: _value.currentIndex
    property alias valueRef: _value

    anchors.left: parent.left
    anchors.right: parent.right
    height: _panel.contentHeight + header.height + _panel.content.anchors.topMargin * 2

    header.title.text: name
    Item {
        id: _property
        height: _panel.contentHeight
        anchors.left: parent.left
        anchors.right: parent.right

        Label {
            id: _label
            text: qsTr("Value selected :")
            anchors.left: parent.left
            height: _panel.contentHeight
            verticalAlignment: Text.AlignVCenter
            color: "#ffffff"
        }
        ComboBox {
            id: _value
            height: contentHeight
            model: _panel.model
            anchors.right: parent.right
            anchors.left: _label.right
            anchors.leftMargin: 5
        }
    }

}
