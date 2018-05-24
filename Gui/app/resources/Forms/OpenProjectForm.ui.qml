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
        color: AppSettings.theme["background"]["color"]
    }

    FileDialog {
        id: fileDialog
        title: "Please choose a project"
        selectMultiple: false
        nameFilters: ["DNAI project (*.dnaisolution)"]
    }

    header: TabBar {
        width: parent.width
        TabButton {
            contentItem: Title2 {
                padding: 10
                text: qsTr("Open a project")
            }
            background: Rectangle {
                color: AppSettings.theme["background"]["color"]
            }
        }
        background: Rectangle {
            color: AppSettings.theme["background"]["color"]
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
            color: AppSettings.theme["text"]["accentColor"]
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
                border.color: AppSettings.theme["border"]["color"]
                border.width: AppSettings.theme["border"]["width"]
                color: AppSettings.theme["background"]["darkColor"]
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
            color: AppSettings.theme["text"]["accentColor"]
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
    footer: Item {
        height: 40
        Button {
            id: cancelButton
            anchors.left: parent.left
            leftPadding: 20
            rightPadding: 20
            contentItem: Text {
                text: qsTr("Cancel")
                color: AppSettings.theme["text"]["color"]
                font.family: AppSettings.theme["font"]["family"]
                font.pixelSize: AppSettings.theme["font"]["pixelSize"]
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            background: Rectangle {
                color: AppSettings.theme["background"]["color"]
            }
        }
        Button {
            id: openButton
            anchors.right: parent.right
            leftPadding: 20
            rightPadding: 20
            contentItem: Text {
                text: qsTr("Open")
                color: AppSettings.theme["text"]["color"]
                font.family: AppSettings.theme["font"]["family"]
                font.pixelSize: AppSettings.theme["font"]["pixelSize"]
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            background: Rectangle {
                color: AppSettings.theme["background"]["color"]
            }
        }
    }
}
