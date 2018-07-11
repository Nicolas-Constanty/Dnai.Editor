import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 2.2

import QtGraphicalEffects 1.0 as Qg

import Dnai.Controls 1.0
import Dnai.FontAwesome 1.0
import Dnai.Settings 1.0
import Dnai.Theme 1.0

import "../Components"

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
            Label {
                text: "Settings"
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

        //Theme selection panel
        SettingsItem {
            height: 40
            anchors.left: parent.left
            anchors.right: parent.right
            text: "Selected theme"
            content: Component {
                ComboBox {
                    anchors.verticalCenter: parent.verticalCenter
                    height: 26
                    Component.onCompleted:
                    {
                        model = AppSettings.themeNames
                    }
                    onCurrentTextChanged: {
                        AppSettings.currentTheme = currentText
                    }
                }
            }
        }
        Rectangle {
            height: AppSettings.theme["border"]["width"]
            anchors.left: parent.left
            anchors.right: parent.right
            color: AppSettings.theme["border"]["color"]
        }

        //Input/output color selection
        IoSettings {
            height: 40
            colorWheel.backgroundColor: _control.background.color
            anchors.left: parent.left
            anchors.right: parent.right
        }
    }
}
