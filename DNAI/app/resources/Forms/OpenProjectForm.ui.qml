import QtQuick 2.4
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.2

import DNAI 1.0

import "../Panels"
import "../Components"
import "../Style"

Page {
    id: page
    property alias fileDialog: fileDialog
    property alias chooseButton: chooseButton
    property alias cancelButton: cancelButton
    property alias openButton: openButton
    property alias projectPath: projectPath
    property alias viewData: viewData
    property alias filesData: filesData
    property bool isConnected: false

    background: Rectangle {
        color: AppSettings.style.background.color
    }

    FileDialog {
        id: fileDialog
        title: "Please choose a project"
        selectMultiple: false
        nameFilters: ["DNAI project (*.dnaiproject)"]
    }

    header: TabBar {
        width: parent.width
        TabButton {
            contentItem: Title2 {
                padding: 10
                text: qsTr("Open a project")
            }
            background: Rectangle {
                color: AppSettings.style.background.color
            }
        }
        background: Rectangle {
            color: AppSettings.style.background.color
        }
    }

    contentChildren: BasePanel {
        spacing: 4
        anchors.fill: parent
        Item {
            anchors.left: parent.left
            anchors.right: parent.right
            height: chooseButton.height
            TextField {
                id: projectPath
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.right: chooseButton.left
                anchors.left: parent.left
                placeholderText: qsTr("Choose a project")
                text: fileDialog.fileUrl
                readOnly: true
            }
            Button {
                id: chooseButton
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                text: qsTr("Choose")
            }
        }
        Splitter {
            visible: isConnected
        }
        Title3 {
            visible: isConnected
            anchors.left: parent.left
            anchors.right: parent.right
            text: qsTr("Online Projects")
            color: AppSettings.style.text.accentColor
            horizontalAlignment: Qt.AlignHCenter
        }
        ScrollView {
            visible: isConnected
            padding: 10
            anchors.left: parent.left
            anchors.right: parent.right
            height: 200
            background: Rectangle {
                anchors.fill: parent
                border.color: AppSettings.style.border.color
                border.width: AppSettings.style.border.width
                color: AppSettings.style.background.darkColor
            }

            ListView {
                anchors.fill: parent
                anchors.margins: 20
                spacing: 4
                model: ListModel {
                    id: filesData
                }
                clip: true
                delegate: onlineFilesDelegate
            }
        }
        Splitter {
        }
        Title3 {
            anchors.left: parent.left
            anchors.right: parent.right
            text: qsTr("Informations")
            color: AppSettings.style.text.accentColor
            horizontalAlignment: Qt.AlignHCenter
        }
        ScrollView {
            anchors.left: parent.left
            anchors.right: parent.right
            height: 100
            ListView {
                anchors.left: parent.left
                anchors.right: parent.right
                clip: true
                spacing: 4
                model: ListModel {
                    id: viewData
                }
                delegate: Text {
                    text: field + ": " + value
                }
            }
        }
    }
    footer: ToolBar {
        height: 40
        background: Rectangle {
            height: 40
            color: AppSettings.style.background.color
        }
        ToolButton {
            id: cancelButton
            anchors.left: parent.left
            leftPadding: 20
            rightPadding: 20
            contentItem: Text {
                text: qsTr("Cancel")
                color: AppSettings.style.text.color
                font.family: AppSettings.style.font.family
                font.pixelSize: AppSettings.style.font.pixelSize
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            background: Rectangle {
                color: AppSettings.style.background.color
            }
        }
        ToolButton {
            id: openButton
            anchors.right: parent.right
            leftPadding: 20
            rightPadding: 20
            contentItem: Text {
                text: qsTr("Open")
                color: AppSettings.style.text.color
                font.family: AppSettings.style.font.family
                font.pixelSize: AppSettings.style.font.pixelSize
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            background: Rectangle {
                color: AppSettings.style.background.color
            }
        }
    }
}
