import QtQuick 2.9
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.2

import DNAI 1.0

import "../Style"
import "../Panels"

Page {
    property alias fileDialog: _fileDialog
    property alias chooseButton: solutionButton
    property alias cancelButton: cancelButton
    property alias createButton: createButton

    property alias solutionPath: solutionPath
    property alias solutionName: solutionName
    property alias solutionDescription: solutionDescription

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
                text: qsTr("Create a Solution")
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
        id: _fileDialog
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
            height: solutionPath.height
            MLabel {
                id: solutionLabel
                text: qsTr("Solution path : ")
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                horizontalAlignment: Qt.AlignLeft
                width: 100
            }
            TextField {
                id: solutionPath
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: solutionLabel.right
                anchors.right: solutionButton.left
                placeholderText: qsTr("Choose a folder")
                text: _fileDialog.fileUrl
                readOnly: true
            }
            Button {
                id: solutionButton
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
            height: solutionName.height
            MLabel {
                id: namesolutionLabel
                text: qsTr("Name : ")
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                width: 100
                horizontalAlignment: Qt.AlignLeft
            }
            TextField {
                id: solutionName
                anchors.left: namesolutionLabel.right
                anchors.right: parent.right
                placeholderText: qsTr("Choose a solution name")
            }
        }
        Item {
            anchors.left: parent.left
            anchors.right: parent.right
            height: solutionDescription.height
            MLabel {
                id: descriptionsolutionLabel
                text: qsTr("Description : ")
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                horizontalAlignment: Qt.AlignLeft
                width: 100
            }
            TextField {
                id: solutionDescription
                anchors.left: descriptionsolutionLabel.right
                anchors.right: parent.right
                placeholderText: qsTr("Choose a solution description")
            }
        }

        Item {
            anchors.left: parent.left
            anchors.right: parent.right
            height: projectName.height
            MLabel {
                id: nameProjectLabel
                text: qsTr("Name : ")
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                width: 100
                horizontalAlignment: Qt.AlignLeft
            }
            TextField {
                id: projectName
                anchors.left: nameProjectLabel.right
                anchors.right: parent.right
                placeholderText: qsTr("Choose a solution name")
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
                placeholderText: qsTr("Choose a solution description")
            }
        }
    }
    footer: Item {
        height: 40
        width: _page.width
        Button {
            id: cancelButton
            anchors.left: parent.left
            leftPadding: 20
            rightPadding: 20
            contentItem: Text {
                text: qsTr("Cancel")
                color: AppSettings.style.text.color
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            background: Item {
            }
        }
        Button {
            id: createButton
            anchors.right: parent.right
            leftPadding: 20
            rightPadding: 20
            contentItem: Text {
                text: qsTr("Create")
                color: AppSettings.style.text.color
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            background: Item {
            }
        }
    }
}
