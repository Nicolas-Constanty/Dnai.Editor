import QtQuick 2.0
import QtQuick.Controls 2.2

import Dnai.Controls 1.0
import Dnai.FontAwesome 1.0
import Dnai.Settings 1.0
import Dnai.Theme 1.0

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
                        width: parent.width - labelLabel.width - selectedLabel.width - 2 * splitterLabel.width - _rowLabel.spacing * 4
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
                }
            }
            Rectangle {
                height: AppSettings.theme["border"]["width"]
                anchors.left: parent.left
                anchors.right: parent.right
                color: AppSettings.theme["border"]["color"]
            }
            ListModel {
                id: libraryModel
                ListElement {
                    selected: false
                    folderName: "Img_0"
                    label: "0"
                }
                ListElement {
                    selected: false
                    folderName: "Img_1"
                    label: "1"
                }
                ListElement {
                    selected: false
                    folderName: "Img_2"
                    label: "2"
                }
                ListElement {
                    selected: false
                    folderName: "Img_3"
                    label: "3"
                }
                ListElement {
                    selected: false
                    folderName: "Img_4"
                    label: "4"
                }
            }
            Repeater {
                id: _folderList
//                        model: libraryModel
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
                            checked: model.selected
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        Rectangle {
                            id: splitter
                            width: AppSettings.theme["border"]["width"]
                            height: 40
                            color: AppSettings.theme["border"]["color"]
                        }
                        Label {
                            width: parent.width - labelText.width - selectedBox.width - 2 * splitter.width - _row.spacing * 4
                            text: model.folderName
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
                            text: model.label
                            horizontalAlignment: "AlignHCenter"
                            anchors.verticalCenter: parent.verticalCenter
                            enableBar: false
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
