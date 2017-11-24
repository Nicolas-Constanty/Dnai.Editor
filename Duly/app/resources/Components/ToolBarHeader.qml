import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import Utils 1.0

import "../Panels"
import "../Controls"

Item {
    property alias menuEditRef: menuEdit
    property alias heightButton: toolButton.height

    ToolBar {
        width: parent.width
        spacing: 0
        background: Rectangle {
            color: DulySettings.style.background
        }
        ScrollView {
            anchors.fill: parent
            RowLayout {
                spacing: 0
                anchors.fill: parent
                DToolButton {
                    id: toolButton
                    text: qsTr("File")
                    font: menuItem.font

                    onClicked: menuFile.open()
                    DMenu {
                        id: menuFile

                        DMenuItem {
                            id: menuItem
                            font.pixelSize: DulySettings.style.font.pixelSize
                            font.family: DulySettings.style.font.family
                            text: qsTr("New window")
                        }
                        DMenuItem {
                            text: qsTr("New project")
                            font: menuItem.font
                            onClicked: newProjectPopup.open()
                        }
                        DMenuItem {
                            text: qsTr("Open project")
                            onClicked: openProjectPopup.open()
                            font: menuItem.font
                        }
                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Save")
                        }
                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Save as")
                        }
                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Save all")
                        }
                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Close window")
                        }
                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Exit")
                        }
                    }
                }

                DToolButton {

                    text: qsTr("Edit")
                    onClicked: menuEdit.open()
                    font: menuItem.font

                    DMenu {
                        id: menuEdit
                        y: parent.height
                        property alias settingRef: settingPanel
                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Undo")
                        }
                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Redo")
                        }
                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Cut")
                        }
                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Copy")
                        }
                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Past")
                        }
                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Delete")
                        }
                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Select all")
                        }
                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Invert all")
                        }
                        DMenuItem {
                            font: menuItem.font
                            text: "Settings"
                            onClicked: popup.open()
                        }
                    }
                }

                DToolButton {
                    text: qsTr("View")
                    onClicked: menuView.open()
                    font: menuItem.font

                    DMenu {
                        id: menuView
                        y: parent.height
                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Toogle full screen")
                        }
                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Toogle menu bar")
                        }
                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Toogle left panel")
                            onClicked: {
                                if (root.layout.leftPanel.state == "Visible")
                                    root.layout.leftPanel.state = "Invisible"
                                else
                                    root.layout.leftPanel.state = "Visible"
                            }
                        }
                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Toogle right panel")
                            onClicked: {
                                if (root.layout.rightPanel.state == "Visible")
                                    root.layout.rightPanel.state = "Invisible"
                                else
                                    root.layout.rightPanel.state = "Visible"
                            }
                        }
                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Font size up")
                        }
                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Font size down")
                        }
                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Reset font size")
                        }
                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Toogle console")
                            onClicked: {
                                if (root.layout.debugConsole.state == "Visible")
                                    root.layout.debugConsole.state = "Invisible"
                                else
                                    root.layout.debugConsole.state = "Visible"
                            }
                        }
                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Toogle property panel")
                        }
                    }
                }

                DToolButton {
                    text: qsTr("Panes")
                    onClicked: menuPanes.open()
                    font: menuItem.font

                    DMenu {
                        id: menuPanes
                        y: parent.height

                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Split left")
                        }
                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Split right")
                        }
                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Split up")
                        }
                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Split down")
                        }
                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Next pane")
                        }
                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Prev pane")
                        }
                    }

                }

                DToolButton {
                    text: qsTr("Tab")
                    onClicked: menuTab.open()
                    font: menuItem.font

                    DMenu {
                        id: menuTab
                        y: parent.height

                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Next tab")
                        }

                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Prev tab")
                        }

                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Close tab")
                        }

                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("History")
                        }
                    }
                }

                DToolButton {
                    text: qsTr("Viewport")
                    onClicked: viewportTab.open()
                    font: menuItem.font

                    DMenu {
                        id: viewportTab
                        y: parent.height

                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Zoom in")
                        }

                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Zoom out")
                        }

                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Move")
                        }

                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Add node")
                        }

                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Resize node")
                        }

                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Format node")
                        }

                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Collapse node")
                        }

                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Expand node")
                        }

                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Open node")
                        }

                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Open blank node")
                        }

                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Link")
                        }

                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Unlink")
                        }
                    }
                }

                DToolButton {
                    text: qsTr("Node")
                    onClicked: nodeTab.open()
                    font: menuItem.font

                    DMenu {
                        id: nodeTab
                        y: parent.height

                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("New node")
                        }

                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Delete node")
                        }

                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Import node")
                        }

                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Export node")
                        }
                    }
                }

                DToolButton {
                    text: qsTr("Run")
                    onClicked: runTab.open()
                    font: menuItem.font

                    DMenu {
                        font: menuItem.font
                        id: runTab
                        y: parent.height

                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Build")
                        }

                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Run")
                        }

                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Run debug")
                        }

                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Pause")
                        }

                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Stop")
                        }
                    }
                }
                DToolButton {
                    text: qsTr("Cloud")
                    onClicked: cloudTab.open()
                    font: menuItem.font


                    DMenu {
                        id: cloudTab
                        y: parent.height
                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Upload")
                        }

                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Download")
                        }

                        DMenuItem {
                            font: menuItem.font
                            text: qsTr("Store")
                        }
                    }
                }
            }
        }
    }

    //SETTINGS PANEL
    Popup {
        id: popup
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
    Popup {
        id: newProjectPopup
        x: parent.width / 2 - width / 2
        y: appWindow.height / 2 - height / 2
        width: 640
        height: 480
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
        contentItem: NewProject {
            anchors.fill: parent
            id: newFileProjectPanel
            popup: newProjectPopup
        }
    }
    Popup {
        id: openProjectPopup
        x: parent.width / 2 - width / 2
        y: appWindow.height / 2 - height / 2
        width: 640
        height: 480
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
        contentItem: OpenProject {
            anchors.fill: parent
            id: openProjectPanel
            popup: openProjectPopup
        }
    }
}
