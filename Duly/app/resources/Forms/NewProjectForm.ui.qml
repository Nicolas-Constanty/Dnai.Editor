import QtQuick 2.9
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Page {
    property alias fileDialog: fileDialog
    property alias chooseButton: pathButton
    property alias cancelButton: cancelButton
    property alias createButton: createButton
    property alias projectPath: projectPath
    property alias projectName: projectName
    property alias projectDescription: projectDescription

    FileDialog {
        id: fileDialog
        title: "Please choose a path"
        folder: shortcuts.home
        selectFolder: true
        selectMultiple: false
    }
    TabBar {
        width: parent.width
        TabButton {
            text: qsTr("Create a new project")
        }
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
                text: qsTr("Create in : ")
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
        RowLayout {
            anchors.left: parent.left
            anchors.right: parent.right
            Label {
                id: nameLabel
                text: qsTr("Name : ")
                anchors.left: parent.left
            }
            TextField {
                id: projectName
                anchors.leftMargin: 20
                anchors.left: nameLabel.right
                anchors.right: parent.right
                placeholderText: qsTr("Choose a project name")
            }
        }
        RowLayout {
            anchors.left: parent.left
            anchors.right: parent.right
            Label {
                id: descriptionLabel
                text: qsTr("Description : ")
                anchors.left: parent.left
            }
            TextField {
                id: projectDescription
                anchors.leftMargin: 20
                anchors.left: descriptionLabel.right
                anchors.right: parent.right
                placeholderText: qsTr("Choose a project description")
            }
        }
    }

    footer: ToolBar {
        ToolButton {
            id: cancelButton
            anchors.left: parent.left
            leftPadding: 20
            rightPadding: 20
            text: qsTr("Cancel")
        }
        ToolButton {
            id: createButton
            anchors.right: parent.right
            leftPadding: 20
            rightPadding: 20
            text: qsTr("Create")
        }
    }
}
