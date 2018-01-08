import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import Qt.labs.settings 1.0

import Utils 1.0

Item {
    property alias name: label.text
    property alias items: comboBox
    property alias listModel: comboBox.model

    Settings {
        category: "Theme/" + name
        property alias current: comboBox.currentIndex
    }

    anchors.right: parent.right
    anchors.rightMargin: 0
    anchors.left: parent.left
    anchors.leftMargin: 0

    Rectangle {
        height: 40
        Layout.preferredHeight: 40
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        color: "transparent"
        Layout.fillWidth: false
        id: colorPickerForm
        RowLayout {
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            Label {
                id: label
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.verticalCenter: parent.verticalCenter
                color: DulySettings.style.text.color
                font.family: DulySettings.style.font.family
                font.pixelSize: DulySettings.style.font.pixelSize
            }
            ComboBox {
                id: comboBox
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                textRole: qsTr("")
                currentIndex: 0
            }
        }
    }
}
