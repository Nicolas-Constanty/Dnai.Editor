import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.3

import Dnai.Controls 1.0
import Dnai.FontAwesome 1.0
import Dnai.Settings 1.0
import Dnai.Theme 1.0

import DNAI 1.0

Popup {
    id: _control
    modal: true
    focus: true
    padding: 20
    topPadding: 10
    width: 700
    property alias model: _folderList.model
    enter: Transition {
        NumberAnimation { property: "opacity"; from: 0.0; to: 1.0 ;duration: 200}
    }

    background: Rectangle {
        border.width:  AppSettings.theme["border"]["width"]
        border.color: AppSettings.theme["border"]["color"]
        color: AppSettings.theme["colors"]["background"]["base"]
        ButtonAwesomeSolid {
            color: AppSettings.theme["text"]["color"]
            text: "\uf00d"
            height: 20
            width: 20
            anchors.right: parent.right
            anchors.top: parent.top
            background: Item {
            }
            onClicked: {
                _control.close()
            }
        }
    }

    FileDialog {
        id: _fd
        title: "Select a dataset folder"
        folder: Qt.resolvedUrl(StandardPath.writableLocation((StandardPath.HomeLocation)))
        selectFolder : true
        selectExisting: true

        onAccepted: {
            var res = Editor.mlHandler.dataset.createFromPath(_fd.fileUrl)
            if (res !== null)
            {
                console.log(res, res.labels)
                _control.model = res.labels
            }
        }
    }

    Column {
        anchors.left: parent.left
        anchors.right: parent.right
        spacing: 0
        clip: true
        Item {
            id: _title
            height: childrenRect.height + 20
            anchors.left: parent.left
            anchors.right: parent.right
            Label {
                text: "Dataset"
                font.pointSize: 14
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }

        Column {
            visible: typeof(_control.model) === "undefined"
            anchors.left: parent.left
            anchors.right: parent.right
            spacing: 0
            Item {
                height: 80
                anchors.left: parent.left
                anchors.right: parent.right
                Button {
                    text: "Select a dataset folder"
                    awesomeIcon.text: "\uf07c"
                    awesomeIcon.size: 20
                    anchors.centerIn: parent
                    onClicked: {
                        _fd.open()
                    }
                }
            }
        }

        Column {
            visible: typeof(_control.model) !== "undefined"
            anchors.left: parent.left
            anchors.right: parent.right
            spacing: 0
            Item {
                height: 40
                anchors.left: parent.left
                anchors.right: parent.right
                Row {
                    id: _rowLabel
                    spacing: 10
                    anchors.fill: parent
                    Label {
                        id: selectedLabel
                        width: 60
                        text: "Selected"
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    Rectangle {
                        id: splitterLabel
                        width: AppSettings.theme["border"]["width"]
                        height: 40
                        color: AppSettings.theme["border"]["color"]
                    }
                    Label {
                        width: parent.width - labelLabel.width - selectedLabel.width - 2 * splitterLabel.width - _rowLabel.spacing * 6 - labelCount.width
                        text: "Folder name"
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    Rectangle {
                        width: AppSettings.theme["border"]["width"]
                        height: 40
                        color: AppSettings.theme["border"]["color"]
                    }
                    Label {
                        id: labelLabel
                        width: 200
                        text: "Label"
                        horizontalAlignment: "AlignHCenter"
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    Rectangle {
                        width: AppSettings.theme["border"]["width"]
                        height: 40
                        color: AppSettings.theme["border"]["color"]
                    }
                    Label {
                        id: labelCount
                        width: 80
                        text: "Count"
                        horizontalAlignment: "AlignHCenter"
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
            }
            Rectangle {
                height: AppSettings.theme["border"]["width"] * 2
                anchors.left: parent.left
                anchors.right: parent.right
                color: AppSettings.theme["border"]["color"]
            }
            Repeater {
                id: _folderList
                anchors.left: parent.left
                anchors.right: parent.right
                delegate: Item {
                    height: 40
                    anchors.left: parent.left
                    anchors.right: parent.right
                    Row {
                        id: _row
                        spacing: 10
                        anchors.fill: parent
                        CheckBox {
                            id: selectedBox
                            width: 60
                            checked: model.obj.selected
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        Rectangle {
                            id: splitter
                            width: AppSettings.theme["border"]["width"]
                            height: 40
                            color: AppSettings.theme["border"]["color"]
                        }
                        Label {
                            width: parent.width - labelText.width - selectedBox.width - 2 * splitter.width - _row.spacing * 6 - labelcount.width
                            text: model.key
                            horizontalAlignment: "AlignLeft"
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        Rectangle {
                            width: AppSettings.theme["border"]["width"]
                            height: 40
                            color: AppSettings.theme["border"]["color"]
                        }
                        TextField {
                            id: labelText
                            width: 200
                            text: model.obj.value
                            horizontalAlignment: "AlignHCenter"
                            anchors.verticalCenter: parent.verticalCenter
                            enableBar: false
                        }
                        Rectangle {
                            width: AppSettings.theme["border"]["width"]
                            height: 40
                            color: AppSettings.theme["border"]["color"]
                        }
                        Label {
                            id: labelcount
                            width: 80
                            text: model.obj.count
                        }
                    }
                    Rectangle {
                        height: AppSettings.theme["border"]["width"]
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
                        color: AppSettings.theme["border"]["color"]
                    }
                }
            }

            Item {
                height: 40
                anchors.left: parent.left
                anchors.right: parent.right
                CheckBox {
                    id: _autogenerate
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Auto generate .csv"
                    checked: true
                }
            }
            Item {
                height: 40
                anchors.left: parent.left
                anchors.right: parent.right
                CheckBox {
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Suffle data"
                    checked: true
                }
            }
            Item {
                height: 40
                anchors.left: parent.left
                anchors.right: parent.right
                Row {
                    anchors.fill: parent
                    spacing: 10
                    Label {
                        id: _labelExisting
                        enabled: !_autogenerate.checked
                        text: "Use existing .csv"
                    }
                    TextField {
                        width: parent.width - _labelExisting.width - _browse.width - parent.spacing * 3
                        enabled: !_autogenerate.checked
                    }
                    Button {
                        id: _browse
                        text: "Browse"
                        width: 200
                        enabled: !_autogenerate.checked
                    }
                }
            }
        }
    }
}
