import QtQuick 2.4
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import Utils 1.0

Page {
    property alias fileDialog: fileDialog
    property alias chooseButton: pathButton
    property alias cancelButton: cancelButton
    property alias openButton: openButton
    property alias projectPath: projectPath
    property alias viewData: viewData

    background: Rectangle {
        color: DulySettings.style.background
    }

    FileDialog {
        id: fileDialog
        title: "Please choose a project"
        folder: shortcuts.home
        selectMultiple: false
        nameFilters: ["Duly project (*.dulyproject)"]
    }
    TabBar {
        width: parent.width
        TabButton {
            contentItem: Text {
                text: qsTr("Open a project")
                color: DulySettings.style.text.color
                font.family: DulySettings.style.font.family
                font.pixelSize: DulySettings.style.font.pixelSize
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            background: Rectangle {
                color: DulySettings.style.background
            }
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
                text: qsTr("Open : ")
                anchors.left: parent.left
                color: DulySettings.style.text.color
                font.family: DulySettings.style.font.family
                font.pixelSize: DulySettings.style.font.pixelSize
            }
            TextField {
                id: projectPath
                anchors.leftMargin: 20
                anchors.rightMargin: 50
                anchors.left: pathLabel.right
                anchors.right: pathButton.left
                placeholderText: qsTr("Choose a project")
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
            Rectangle {
                width: parent.width
                height: viewData.count * 18
                color: "#80FFFFFF"
                radius: 10
                ListView {
                    id: list
                    anchors.fill: parent
                    anchors.topMargin: 10
                    anchors.leftMargin: 15
                    model: ListModel {
                        id: viewData
                    }
                    delegate: Text {
                        text: field + ": " + value
                    }
                }
            }
        }
    }

    footer: ToolBar {
        background: Rectangle {
            implicitHeight: 40
            color: DulySettings.style.background
        }
        ToolButton {
            id: cancelButton
            anchors.left: parent.left
            leftPadding: 20
            rightPadding: 20
            contentItem: Text {
                text: qsTr("Cancel")
                color: DulySettings.style.text.color
                font.family: DulySettings.style.font.family
                font.pixelSize: DulySettings.style.font.pixelSize
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            background: Rectangle {
                color: DulySettings.style.background
            }
        }
        ToolButton {
            id: openButton
            anchors.right: parent.right
            leftPadding: 20
            rightPadding: 20
            contentItem: Text {
                text: qsTr("Open")
                color: DulySettings.style.text.color
                font.family: DulySettings.style.font.family
                font.pixelSize: DulySettings.style.font.pixelSize
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            background: Rectangle {
                color: DulySettings.style.background
            }
        }
    }
}
