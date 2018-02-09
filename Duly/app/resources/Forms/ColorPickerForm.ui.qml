import QtQuick 2.9
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.2
import Qt.labs.settings 1.0

import Utils 1.0
import "../Style"

Item {
    id: item1
    property alias name: label.text
    property alias button: selectButton
    property alias colorDialogRef: colorDialog
    property int mainHeight: 50
    property alias colorSetting: settings.colorSelected

    Settings {
        id: settings
        category: name
        property alias colorSelected: colorSelect.color
    }
    Item {
        height: mainHeight
        anchors.right: parent.right
        anchors.left: parent.left
        id: colorPickerForm
        MLabel {
            id: label
            text: qsTr("Label")
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
        }
        Button {
            id: selectButton
            width: 30
            height: 30
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            background: Rectangle {
                id: colorSelect
                color: colorDialogRef.color
                border.width: 2
                radius: 4
            }
        }
    }

    ColorDialog {
        id: colorDialog
        width: 150
        height: 150
        title: "Please choose a color"
    }
}
