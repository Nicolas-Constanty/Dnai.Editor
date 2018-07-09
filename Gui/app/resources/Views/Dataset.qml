import QtQuick 2.0
import QtQuick.Controls 2.2

import Dnai.Controls 1.0
import Dnai.FontAwesome 1.0
import Dnai.Settings 1.0

import "../Components"
import "../Style"

Popup {
    id: _control
    modal: true
    focus: true
    padding: 20
    topPadding: 10
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
        //            visible: _control.opacity == 1.0
        anchors.left: parent.left
        anchors.right: parent.right
        spacing: 0
        clip: true
        Item {
            id: _title
            height: childrenRect.height + 40
            anchors.left: parent.left
            anchors.right: parent.right
            MLabel {
                text: "Dataset"
                font.pointSize: 14
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }


        Item {
            height: 40
            anchors.left: parent.left
            anchors.right: parent.right
            Row {
                id: _rowLabel
                spacing: 10
                anchors.fill: parent
                MLabel {
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
                MLabel {
                    width: parent.width - labelLabel.width - selectedLabel.width - 2 * splitterLabel.width - _rowLabel.spacing * 4
                    text: "Folder name"
                    anchors.verticalCenter: parent.verticalCenter
                }
                Rectangle {
                    width: AppSettings.theme["border"]["width"]
                    height: 40
                    color: AppSettings.theme["border"]["color"]
                }
                MLabel {
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
            model: libraryModel
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
                    MLabel {
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
                    EditableText {
                        id: labelText
                        width: 200
                        text: model.label
                        horizontalAlignment: "AlignHCenter"
                        anchors.verticalCenter: parent.verticalCenter
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
    }

}
