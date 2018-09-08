import QtQuick 2.9
import QtQuick.Controls 2.2
import Qt.labs.settings 1.0

import DNAI 1.0
import Dnai.Theme 1.0

import "../Style"

Item {
    property alias name: label.text
    property alias items: comboBox
    property alias listModel: comboBox.model

    Settings {
        category: "Theme/" + name
        property alias current: comboBox.currentIndex
    }

    anchors.right: parent.right
    anchors.left: parent.left
    height: 40

    Item {
        height: 40
        anchors.right: parent.right
        anchors.left: parent.left
        id: colorPickerForm
        Label {
            id: label
            height: parent.height
            anchors.left: parent.left
        }
        ComboBox {
            id: comboBox
            anchors.right: parent.right
            textRole: qsTr("")
            currentIndex: 0
        }
    }
}
