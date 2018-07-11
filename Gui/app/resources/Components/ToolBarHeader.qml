import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.2

import DNAI 1.0
import Dnai.FontAwesome 1.0
import Dnai.Settings 1.0

import "../Panels"
import "../Controls"
import "../Style"
import "../Views"

ToolBar {
    property alias menuEditRef: menuEdit
    id: toolBar
    width: parent.width
    height: 40
    spacing: 0
    background: Rectangle {
        color: AppSettings.theme["colors"]["background"]["base"]
    }

    Action {
        id: newProjectAction
        text: qsTr("New Solution")
        onTriggered: Editor.mainView().newProjectPopup.open()
        shortcut: StandardKey.New
    }
    Action {
        id: openAction
        text: qsTr("Open Solution")
        onTriggered: Editor.mainView().openProjectId.open()
        shortcut: StandardKey.Open
    }
    Action {
        id: saveAction
        text: qsTr("Save")
        onTriggered: Editor.solution.selectedProject().save()
        enabled: Editor.loaded
        shortcut: StandardKey.Save
    }
    Action {
        id: saveAsAction
        text: qsTr("Save as")
        enabled: Editor.loaded
        shortcut: StandardKey.SaveAs
    }
    Action {
        id: saveAllAction
        text: qsTr("Save all")
        onTriggered: Editor.solution.save()
        enabled: Editor.loaded
    //    shortcut: StandardKey.SaveAll
    }

    Action {
        id: settingsAction
        text: qsTr("Settings")
        onTriggered: settingsPopup.open()
        shortcut: StandardKey.Preferences
    }

    Action {
        id: fullscreenAction
        text: qsTr("Toogle full screen")
        onTriggered: {
            if (appWindow.visibility != Window.FullScreen)
                appWindow.visibility = Window.FullScreen
            else
                appWindow.visibility = Window.Windowed
        }
        shortcut: StandardKey.FullScreen
    }

    Action {
        id: datasetsAction
        onTriggered: datasetPopup.open()
        text: qsTr("Create/Import dataset")
    }

  /*  Action {
        id: leftPanelAction
        text: qsTr("Toogle left panel")
        enabled: Editor.loaded
        onTriggered: {
            var leftPanel = appWindow.layout.getPanel("panelLeft")
            if (leftPanel.state === "Visible")
                leftPanel.state = "Invisible"
            else
                leftPanel.state = "Visible"
        }
        //shortcut: StandardKey.
    }

    Action {
        id: rightPanelAction
        text: qsTr("Toogle right panel")
        enabled: Editor.loaded
        onTriggered: {
            var rightPanel = appWindow.layout.getPanel("panelRight")
            if (rightPanel.state === "Visible")
                rightPanel.state = "Invisible"
            else
                rightPanel.state = "Visible"
        }
        //shortcut: StandardKey.FullScreen
    }*/

    ScrollView {
        anchors.fill: parent
        RowLayout {
            spacing: 0
            anchors.fill: parent
            DToolButton {
                id: toolButton
                text: qsTr("File")

                onButtonPressed: menuFile.open()
                DMenu {
                    id: menuFile
                    y: parent.height

                    DMenuItem {
                        action: newProjectAction
                        iconItem.text: "\uf15b"
                        iconItem.font.pointSize: 8
                    }
                    DMenuItem {
                        action: openAction
                        iconItem.text: "\uf07c"
                        iconItem.font.pointSize: 8
                    }
                    DMenuItem {
                        action: saveAction
                        iconItem.text: "\uf0c7"
                        iconItem.font.pointSize: 8
                    }
                    DMenuItem {
                        action: saveAsAction
                        iconItem.text: "\uf0c7"
                        iconItem.font.pointSize: 8
                    }
                    DMenuItem {
                        action: saveAllAction
                        iconItem.text: "\uf0c7"
                        iconItem.font.pointSize: 8
                    }
                }
            }

            DToolButton {

                text: qsTr("Edit")
                onButtonPressed: menuEdit.open()


                DMenu {
                    id: menuEdit
                    y: parent.height

                    DMenuItem {
                        action: settingsAction
                        iconItem.text: "\uf013"
                        iconItem.font.pointSize: 8
                    }
                }
            }

            DToolButton {
                text: qsTr("View")
                onButtonPressed:  menuView.open()


                DMenu {
                    id: menuView
                    y: parent.height
                    DMenuItem {
                        action: fullscreenAction
                        iconItem.text: "\uf31e"
                        iconItem.font.pointSize: 8
                    }
                }
            }
            DToolButton {

                text: qsTr("ML")
                onButtonPressed: menuML.open()


                DMenu {
                    id: menuML
                    y: parent.height

                    DMenuItem {
                        action: datasetsAction
                        iconItem.text: "\uf013"
                        iconItem.font.pointSize: 8
                    }
                }
            }

        }
    }
    /*Timer {
        id: _timer
        running: false
        interval: 3000
        onTriggered: {
            _buildButton.status = 1
            Editor.onBuildSuccess()
        }
        onRunningChanged: {
            if (running == true)
                _buildButton.status = 3
        }
    }*/

    /*Button {
        property int status: 0
        id: _buildButton
        anchors.centerIn: parent
        background: TextAwesomeSolid {
            text: "\uf013"
            font.pointSize: 18
            color: _buildButton.hovered ? "#FFFFFFFF" : _buildButton.status === 0 ? "#FF606060" : _buildButton.status === 1 ? "#FF8BC34A" : _buildButton.status === 2 ? "#F44336" : "#FFC107"
        }
        onClicked: {
            _timer.start()
            _rotator.start()
          //  Editor.onBuildStart()
        }
        RotationAnimator {
            id: _rotator
            target: _buildButton;
            from: 0;
            to: 360;
            duration: 3000
            running: false
        }
    }*/
    UserMenu {
        id: _usrmenu
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
    }

    //SETTINGS PANEL
    Settings {
        id: settingsPopup
        x: parent.width / 2 - width / 2
        y: appWindow.height / 2 - height / 2
        width: 480
    }

    //DATASET PANEL
    Dataset {
        id: datasetPopup
        x: parent.width / 2 - width / 2
        y: appWindow.height / 2 - height / 2
        width: parent.width / 1.5
    }
}
