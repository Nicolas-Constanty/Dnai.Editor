import QtQuick 2.9
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtQuick.Layouts 1.3
import Qt.labs.settings 1.0

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
    Rectangle {
        height: mainHeight
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        color: "transparent"
        id: colorPickerForm
        RowLayout {
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            Label {
                id: label
                text: qsTr("Label")
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.verticalCenter: parent.verticalCenter
            }
            Button {
                id: selectButton
                width: 30
                height: 30
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.preferredHeight: 30
                Layout.preferredWidth: 30
                Layout.fillWidth: false
                anchors.verticalCenter: parent.verticalCenter
                background: Rectangle {
                    id: colorSelect
                    color: colorDialogRef.color
                    border.width: 2
                    radius: 4
                }
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
