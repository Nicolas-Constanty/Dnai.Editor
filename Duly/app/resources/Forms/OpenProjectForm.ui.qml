import QtQuick 2.4
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import Utils 1.0

Page {
    id: page
    property alias fileDialog: fileDialog
    property alias chooseButton: chooseButton
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

    ListModel {
        id: filesModel
        ListElement{
            filename: "fgjdjgdg"
        }
        ListElement{
            filename: "guygyuug"
        }
        ListElement{
            filename: "yugyugytftyf"
        }
        ListElement{
            filename: "dfghjuih"
        }
        ListElement{
            filename: "ijokpkppkp"
        }
        ListElement{
            filename: "plplllllllllll"
        }
        ListElement{
            filename: "deeeeeee"
        }
        ListElement{
            filename: "eeeeeeeeeeeeeeeeeeee"
        }
        ListElement{
            filename: "eeeeeeee"
        }
        ListElement{
            filename: "nnnnnnnn"
        }
    }

    ColumnLayout {
        anchors.fill: parent
        TabBar {
            Layout.fillWidth: true
            TabButton {
                contentItem: Text {
                    text: qsTr("Open a project")
                    color: DulySettings.style.text.accentColor
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
        ColumnLayout{
            RowLayout {
                Button {
                    id: chooseButton
                    text: qsTr("Choose")
                }
                 TextField {
                     id: projectPath
                     placeholderText: qsTr("Choose a project")
                     text: fileDialog.fileUrl
                     Layout.fillWidth: true
                     readOnly: true
                 }
            }
            Rectangle {
                border.width: 2
                border.color: DulySettings.style.text.accentColor
                Layout.fillWidth: true
                height: 2
            }
            Label {
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: qsTr("Online Projects")
                horizontalAlignment: Text.AlignHCenter
                color: DulySettings.style.text.accentColor
                font.family: DulySettings.style.font.family
                font.pixelSize: DulySettings.style.font.pixelSize
            }
            ScrollView {
                padding: 10
                Layout.fillHeight: true
                Layout.fillWidth: true

                ListView {
                    Layout.fillWidth: true
                    spacing: 4
                    Layout.fillHeight: true
                    model: filesModel
                    clip: true
                    delegate: RowLayout {
                        width: parent.width
                        Text {
                            Layout.fillWidth: true
                            text: filename
                        }
                        Button {
                            text: "Download"
                        }
                    }
                }
            }

            ColumnLayout {
                Rectangle {
                    border.width: 2
                    border.color: DulySettings.style.text.accentColor
                    Layout.fillWidth: true
                    height: 2
                }
                Label {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    text: qsTr("Informations")
                    horizontalAlignment: Text.AlignHCenter
                    color: DulySettings.style.text.accentColor
                    font.family: DulySettings.style.font.family
                    font.pixelSize: DulySettings.style.font.pixelSize
                }
                ScrollView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    height: 100
                    ListView {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
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
        }
    }

//    ColumnLayout {
//        width: parent.width - 40
//        anchors.rightMargin: 20
//        anchors.leftMargin: 20
//        anchors.centerIn: parent
//        RowLayout {
//            anchors.left: parent.left
//            anchors.right: parent.right
//            Button {
//                id: pathButton
//                anchors.right: parent.right
//                text: qsTr("Choose")
//            }

//            TextField {
//                id: projectPath
//                anchors.leftMargin: 20
//                anchors.rightMargin: 50
//                anchors.left: pathLabel.right
//                anchors.right: pathButton.left
//                placeholderText: qsTr("Choose a project")
//                text: fileDialog.fileUrl
//                readOnly: true
//            }
//        }
//        RowLayout {
//            anchors.left: parent.left
//            anchors.right: parent.right
//            Rectangle {
//                width: parent.width
//                height: viewData.count * 18
//                color: "#80FFFFFF"
//                radius: 10
//                ListView {
//                    id: list
//                    anchors.fill: parent
//                    anchors.topMargin: 10
//                    anchors.leftMargin: 15
//                    model: ListModel {
//                        id: viewData
//                    }
//                    delegate: Text {
//                        text: field + ": " + value
//                    }
//                }
//            }
//        }
//    }

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
