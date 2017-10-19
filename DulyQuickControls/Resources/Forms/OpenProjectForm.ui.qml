import QtQuick 2.4
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.2

Page {
    property alias fileDialog: fileDialog
    property alias chooseButton: pathButton
    property alias openButton: openButton
    property alias projectPath: projectPath

    FileDialog {
        id: fileDialog
        title: "Please choose a path"
        folder: shortcuts.home
        selectMultiple: false
        nameFilters: ["Duly project (*.dulyproject)"]
    }
    ColumnLayout {
        width: parent.width - 40
        anchors.rightMargin: 20
        anchors.leftMargin: 20
        anchors.centerIn: parent
        RowLayout {
            anchors.left: parent.left
            anchors.right: parent.right
            Label {
                id: pathLabel
                text: qsTr("Open : ")
                anchors.left: parent.left
            }
            TextField {
                id: projectPath
                anchors.leftMargin: 20
                anchors.rightMargin: 50
                anchors.left: pathLabel.right
                anchors.right: pathButton.left
                placeholderText: qsTr("Choose a folder")
                text: fileDialog.fileUrl
                readOnly: true
            }
            Button {
                id: pathButton
                anchors.right: parent.right
                text: qsTr("Choose")
            }
        }
    }

    footer: ToolBar {
        Material.background: Material.color(Material.Grey, Material.Shade800)
        ToolButton {
            id: openButton
            anchors.right: parent.right
            leftPadding: 20
            rightPadding: 20
            text: qsTr("Open")
        }
    }
}
