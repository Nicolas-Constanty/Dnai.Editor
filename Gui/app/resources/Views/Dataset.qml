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
        spacing: 10
        clip: true
        Item {
            height: childrenRect.height
            anchors.left: parent.left
            anchors.right: parent.right
            MLabel {
                text: "Dataset"
                font.pointSize: 14
                anchors.horizontalCenter: parent.horizontalCenter
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
        ListView {
            model: libraryModel
            anchors.left: parent.left
            anchors.right: parent.right
            delegate: Item {
                height: 40
                anchors.left: parent.left
                anchors.right: parent.right
                Row {
                    anchors.fill: parent
                    CheckBox {
                        checked: model.selected
                    }
                    MLabel {
                        text: model.folderName
                    }
                    EditableText {
                        text: model.label
                    }
                }
            }
        }
    }

}
