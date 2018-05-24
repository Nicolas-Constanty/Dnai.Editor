import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.2

import DNAI 1.0
import Dnai.FontAwesome 1.0

import "../Panels"
import "../Controls"
import "../Style"

ToolBar {
    property alias menuEditRef: menuEdit
    id: toolBar
    width: parent.width
    height: 40
    spacing: 0
    background: Rectangle {
        color: AppSettings.theme["background"]["color"]
    }
    ScrollView {
        anchors.fill: parent
        RowLayout {
            spacing: 0
            anchors.fill: parent
            DToolButton {
                id: toolButton
                text: qsTr("File")

                onClicked: menuFile.open()
                DMenu {
                    id: menuFile
                    y: parent.height
                    //                        DMenuItem {
                    //                            text: qsTr("New window")
                    //                        }
                    DMenuItem {
                        text: qsTr("New project")
                        onClicked: Editor.mainView().newProjectPopup.open()
                    }
                    DMenuItem {
                        text: qsTr("Open project")
                        onClicked:
                        {
                            Editor.mainView().openProjectPopup.open()
                        }
                    }
                    DMenuItem {
                        text: qsTr("Save")
                        onClicked: Editor.solution.selectedProject().save()
                    }
                    DMenuItem {
                        text: qsTr("Save as")
                    }
                    DMenuItem {
                        text: qsTr("Save all")
                        onClicked: Editor.solution.save()
                    }
                    //                        DMenuItem {
                    //                            text: qsTr("Close window")
                    //                        }
                    DMenuItem {
                        text: qsTr("Exit")
                        onClicked: {
                            Qt.quit()
                        }
                    }
                }
            }

            DToolButton {

                text: qsTr("Edit")
                onClicked: menuEdit.open()


                DMenu {
                    id: menuEdit
                    y: parent.height
                    property alias settingRef: settingPanel
                    //                        DMenuItem {
                    //                            text: qsTr("Undo")
                    //                        }
                    //                        DMenuItem {
                    //                            text: qsTr("Redo")
                    //                        }
                    //                        DMenuItem {
                    //                            text: qsTr("Cut")
                    //                        }
                    //                        DMenuItem {
                    //                            text: qsTr("Copy")
                    //                        }
                    //                        DMenuItem {
                    //                            text: qsTr("Past")
                    //                        }
                    //                        DMenuItem {
                    //                            text: qsTr("Delete")
                    //                        }
                    //                        DMenuItem {
                    //                            text: qsTr("Select all")
                    //                        }
                    //                        DMenuItem {
                    //                            text: qsTr("Invert all")
                    //                        }
                    DMenuItem {
                        text: "Settings"
                        onClicked: settingsPopup.open()
                    }
                }
            }

            DToolButton {
                text: qsTr("View")
                onClicked: menuView.open()


                DMenu {
                    id: menuView
                    y: parent.height
                    DMenuItem {
                        text: qsTr("Toogle full screen")
                        onClicked: {
                            if (appWindow.visibility != Window.FullScreen)
                                appWindow.visibility = Window.FullScreen
                            else
                                appWindow.visibility = Window.Windowed
                        }
                    }
                    //                        DMenuItem {
                    //                            text: qsTr("Toogle menu bar")
                    //                        }
                    DMenuItem {
                        text: qsTr("Toogle left panel")
                        onClicked: {
                            var leftPanel = appWindow.layout.getPanel("panelLeft")
                            if (leftPanel.state === "Visible")
                                leftPanel.state = "Invisible"
                            else
                                leftPanel.state = "Visible"
                        }
                    }
                    DMenuItem {
                        text: qsTr("Toogle right panel")
                        onClicked: {
                            var rightPanel = appWindow.layout.getPanel("panelRight")
                            if (rightPanel.state === "Visible")
                                rightPanel.state = "Invisible"
                            else
                                rightPanel.state = "Visible"
                        }
                    }
                    //                        DMenuItem {
                    //                            text: qsTr("Font size up")
                    //                        }
                    //                        DMenuItem {
                    //                            text: qsTr("Font size down")
                    //                        }
                    //                        DMenuItem {
                    //                            text: qsTr("Reset font size")
                    //                        }
                    DMenuItem {
                        text: qsTr("Toogle console")
                        onClicked: {
                            var console = appWindow.layout.getPanel("console")
                            if (console.state === "Visible")
                                console.state = "Invisible"
                            else
                                console.state = "Visible"
                        }
                    }
                    //                        DMenuItem {
                    //                            text: qsTr("Toogle property panel")
                    //                        }
                }
            }

            //                DToolButton {
            //                    text: qsTr("Panes")
            //                    onClicked: menuPanes.open()

            //                    DMenu {
            //                        id: menuPanes
            //                        y: parent.height

            //                        DMenuItem {
            //                            text: qsTr("Split left")
            //                        }
            //                        DMenuItem {
            //                            text: qsTr("Split right")
            //                        }
            //                        DMenuItem {
            //                            text: qsTr("Split up")
            //                        }
            //                        DMenuItem {
            //                            text: qsTr("Split down")
            //                        }
            //                        DMenuItem {
            //                            text: qsTr("Next pane")
            //                        }
            //                        DMenuItem {
            //                            text: qsTr("Prev pane")
            //                        }
            //                    }
            //                }

            //                DToolButton {
            //                    text: qsTr("Tab")
            //                    onClicked: menuTab.open()


            //                    DMenu {
            //                        id: menuTab
            //                        y: parent.height

            //                        DMenuItem {
            //                            text: qsTr("Next tab")
            //                        }

            //                        DMenuItem {
            //                            text: qsTr("Prev tab")
            //                        }

            //                        DMenuItem {
            //                            text: qsTr("Close tab")
            //                        }

            //                        DMenuItem {
            //                            text: qsTr("History")
            //                        }
            //                    }
            //                }

            //                DToolButton {
            //                    text: qsTr("Viewport")
            //                    onClicked: viewportTab.open()


            //                    DMenu {
            //                        id: viewportTab
            //                        y: parent.height

            //                        DMenuItem {
            //                            text: qsTr("Zoom in")
            //                        }
            //                        DMenuItem {
            //                            text: qsTr("Zoom out")
            //                        }
            //                        DMenuItem {
            //                            text: qsTr("Move")
            //                        }
            //                        DMenuItem {
            //                            text: qsTr("Add node")
            //                        }
            //                        DMenuItem {
            //                            text: qsTr("Resize node")
            //                        }
            //                        DMenuItem {
            //                            text: qsTr("Format node")
            //                        }
            //                        DMenuItem {
            //                            text: qsTr("Collapse node")
            //                        }
            //                        DMenuItem {
            //                            text: qsTr("Expand node")
            //                        }
            //                        DMenuItem {
            //                            text: qsTr("Open node")
            //                        }
            //                        DMenuItem {
            //                            text: qsTr("Open blank node")
            //                        }
            //                        DMenuItem {
            //                            text: qsTr("Link")
            //                        }
            //                        DMenuItem {
            //                            text: qsTr("Unlink")
            //                        }
            //                    }
            //                }

            //                DToolButton {
            //                    text: qsTr("Node")
            //                    onClicked: nodeTab.open()


            //                    DMenu {
            //                        id: nodeTab
            //                        y: parent.height

            //                        DMenuItem {
            //                            text: qsTr("New node")
            //                        }
            //                        DMenuItem {
            //                            text: qsTr("Delete node")
            //                        }
            //                        DMenuItem {
            //                            text: qsTr("Import node")
            //                        }
            //                        DMenuItem {
            //                            text: qsTr("Export node")
            //                        }
            //                    }
            //                }

            //                DToolButton {
            //                    text: qsTr("Run")
            //                    onClicked: runTab.open()

            //                    DMenu {

            //                        id: runTab
            //                        y: parent.height

            //                        DMenuItem {
            //                            text: qsTr("Build")
            //                        }

            //                        DMenuItem {
            //                            text: qsTr("Run")
            //                        }

            //                        DMenuItem {
            //                            text: qsTr("Run debug")
            //                        }

            //                        DMenuItem {
            //                            text: qsTr("Pause")
            //                        }

            //                        DMenuItem {
            //                            text: qsTr("Stop")
            //                        }
            //                    }
            //                }
            //                DToolButton {
            //                    text: qsTr("Cloud")
            //                    onClicked: cloudTab.open()



            //                    DMenu {
            //                        id: cloudTab
            //                        y: parent.height
            //                        DMenuItem {
            //                            text: qsTr("Upload")
            //                        }
            //                        DMenuItem {
            //                            text: qsTr("Download")
            //                        }
            //                        DMenuItem {
            //                            text: qsTr("Store")
            //                        }
            //                    }
            //                }
        }
    }
    Timer {
        id: _timer
        running: false
        interval: 3000
        onTriggered: {
            _buildButton.status = 1
        }
        onRunningChanged: {
            if (running == true)
                _buildButton.status = 3
        }
    }
    Button {
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
            Editor.onBuildStart()
        }
        RotationAnimator {
            id: _rotator
            target: _buildButton;
            from: 0;
            to: 360;
            duration: 3000
            running: false
        }
    }
    UserMenu {
        id: _usrmenu
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
    }

    //SETTINGS PANEL
    Modal {
        id: settingsPopup
        background: Rectangle {
            color: AppSettings.theme["background"]["color"]
        }

        x: parent.width / 2 - width / 2
        y: appWindow.height / 2 - height / 2
        width: 640
        height: 480
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
        contentItem: SettingPanel {
            anchors.fill: parent
            id: settingPanel
        }
    }
}
