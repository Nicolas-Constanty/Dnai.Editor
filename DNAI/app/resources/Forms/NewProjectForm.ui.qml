import QtQuick 2.9
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.2

import DNAI 1.0

import "../Style"
import "../Panels"

Page {
    property alias fileDialog: fileDialog
    property alias chooseButton: pathButton
    property alias cancelButton: cancelButton
    property alias createButton: createButton
    property alias projectPath: projectPath
    property alias projectName: projectName
    property alias projectDescription: projectDescription
    width: 1080
    height: 720
    id: _page

    background: Rectangle {
        color: AppSettings.style.background.color
    }

    header: TabBar {
        width: parent.width
        TabButton {
            contentItem: Title2 {
                padding: 10
                text: qsTr("Create a new project")
            }
            background: Rectangle {
                color: AppSettings.style.background.color
            }
        }
        background: Rectangle {
            color: AppSettings.style.background.color
        }
    }
    FileDialog {
        id: fileDialog
        title: "Please choose a path"
        selectFolder: true
        selectMultiple: false
    }

    contentChildren: BasePanel {
        spacing: 20
        topPadding: 150
        anchors.fill: parent
        Item {
            anchors.left: parent.left
            anchors.right: parent.right
            height: projectPath.height
            MLabel {
                id: pathLabel
                text: qsTr("Create in : ")
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                horizontalAlignment: Qt.AlignLeft
                width: 100
            }
            TextField {
                id: projectPath
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: pathLabel.right
                anchors.right: pathButton.left
                placeholderText: qsTr("Choose a folder")
                text: fileDialog.fileUrl
                readOnly: true
            }
            Button {
                id: pathButton
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                width: 100
                text: qsTr("Choose")
            }
        }
        Item {
            anchors.left: parent.left
            anchors.right: parent.right
            height: projectName.height
            MLabel {
                id: nameLabel
                text: qsTr("Name : ")
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                width: 100
                horizontalAlignment: Qt.AlignLeft
            }
            TextField {
                id: projectName
                anchors.left: nameLabel.right
                anchors.right: parent.right
                placeholderText: qsTr("Choose a project name")
            }
        }
        Item {
            anchors.left: parent.left
            anchors.right: parent.right
            height: projectDescription.height
            MLabel {
                id: descriptionLabel
                text: qsTr("Description : ")
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                horizontalAlignment: Qt.AlignLeft
                width: 100
            }
            TextField {
                id: projectDescription
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
        background: Rectangle {
            height: createButton.height
            width: _page.width
            color: AppSettings.style.background.color
        }
    }
}
