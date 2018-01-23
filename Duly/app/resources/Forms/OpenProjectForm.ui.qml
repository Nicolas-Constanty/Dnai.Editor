import QtQuick 2.4
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import Utils 1.0
import "../Style"

Page {
    property alias fileDialog: fileDialog
    property alias chooseButton: pathButton
    property alias cancelButton: cancelButton
    property alias openButton: openButton
    property alias projectPath: projectPath
    property alias viewData: viewData

    background: Rectangle {
        color: DulySettings.style.background.color
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
            contentItem: MText {
                text: qsTr("Open a project")
            }
            background: Rectangle {
                color: DulySettings.style.background.color
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
            MLabel {
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
            color: DulySettings.style.background.color
        }
        ToolButton {
            id: cancelButton
            anchors.left: parent.left
            leftPadding: 20
            rightPadding: 20
            contentItem: MText {
                text: qsTr("Cancel")
            }
            background: Rectangle {
                color: DulySettings.style.background.color
            }
        }
        ToolButton {
            id: openButton
            anchors.right: parent.right
            leftPadding: 20
            rightPadding: 20
            contentItem: MText {
                text: qsTr("Open")
            }
            background: Rectangle {
                color: DulySettings.style.background.color
            }
        }
    }
}
