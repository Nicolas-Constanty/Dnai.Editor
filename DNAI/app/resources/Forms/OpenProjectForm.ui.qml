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
    width: 1080
    height: 720

    FileDialog {
        id: fileDialog
        title: "Please choose a project"
        selectMultiple: false
        nameFilters: ["Duly project (*.dulyproject)"]
    }

    ListModel {
        id: filesModel
        ListElement {
            filename: "fgjdjgdg"
        }
        ListElement {
            filename: "guygyuug"
        }
        ListElement {
            filename: "yugyugytftyf"
        }
        ListElement {
            filename: "dfghjuih"
        }
        ListElement {
            filename: "ijokpkppkp"
        }
        ListElement {
            filename: "plplllllllllll"
        }
        ListElement {
            filename: "deeeeeee"
        }
        ListElement {
            filename: "eeeeeeeeeeeeeeeeeeee"
        }
        ListElement {
            filename: "eeeeeeee"
        }
        ListElement {
            filename: "nnnnnnnn"
        }
    }

    header: TabBar {
        width: parent.width
        TabButton {
            contentItem: Title2 {
                padding: 10
                text: qsTr("Open a project")
            }
            background: Rectangle {
                color: DulySettings.style.background.color
            }
        }
        background: Rectangle {
            color: DulySettings.style.background.color
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
        }
        Title3 {
            anchors.left: parent.left
            anchors.right: parent.right
            text: qsTr("Online Projects")
            color: DulySettings.style.text.accentColor
            horizontalAlignment: Qt.AlignHCenter
        }
        ScrollView {
            padding: 10
            anchors.left: parent.left
            anchors.right: parent.right
            height: 200
            background: Rectangle {
                anchors.fill: parent
                border.color: DulySettings.style.border.color
                border.width: DulySettings.style.border.width
                color: DulySettings.style.background.darkColor
            }

            ListView {
                anchors.fill: parent
                anchors.margins: 20
                spacing: 4
                model: filesModel
                clip: true
                delegate: Item {
                    width: parent.width
                    height: _downloadButton.implicitHeight
                    MLabel {
                        anchors.left: parent.left
                        anchors.right: _downloadButton.left
                        text: filename
                        horizontalAlignment: Qt.AlignLeft
                    }
                    Button {
                        id: _downloadButton
                        text: "Download"
                        anchors.right: parent.right
                    }
                }
            }
        }
        Splitter {
        }
        Title3 {
            anchors.left: parent.left
            anchors.right: parent.right
            text: qsTr("Informations")
            color: DulySettings.style.text.accentColor
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
            color: DulySettings.style.background.color
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
                color: DulySettings.style.background.color
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
                color: DulySettings.style.background.color
            }
        }
    }
}
