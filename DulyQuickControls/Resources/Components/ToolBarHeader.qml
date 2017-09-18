import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.2
import QtQuick.Dialogs 1.2
import "../Panels"

Item {
    property alias menuEditRef: menuEdit
    ToolBar {
        width: parent.width
        Material.background: Material.color(Material.Grey, Material.Shade800)
        spacing: 0
        ScrollView {
            anchors.fill: parent
            RowLayout {
                spacing: 0
               anchors.fill: parent
               ToolButton {
                   text: qsTr("File")
                   onClicked: menuFile.open()

                   Menu {
                       id: menuFile

                       MenuItem {
                           text: qsTr("New window")
                       }
                       MenuItem {
                           text: qsTr("New project")
                       }
                       MenuItem {
                           text: qsTr("Open project")
                       }
                       MenuItem {
                           text: qsTr("Save")
                       }
                       MenuItem {
                           text: qsTr("Save as")
                       }
                       MenuItem {
                           text: qsTr("Save all")
                       }
                       MenuItem {
                           text: qsTr("Close window")
                       }
                       MenuItem {
                           text: qsTr("Exit")
                       }
                   }
               }

               ToolButton {
                   text: qsTr("Edit")
                   onClicked: menuEdit.open()

                   Menu {
                       id: menuEdit
                       property alias settingRef: settingPanel
                       MenuItem {
                           text: qsTr("Undo")
                       }
                       MenuItem {
                           text: qsTr("Redo")
                       }
                       MenuItem {
                           text: qsTr("Cut")
                       }
                       MenuItem {
                           text: qsTr("Copy")
                       }
                       MenuItem {
                           text: qsTr("Past")
                       }
                       MenuItem {
                           text: qsTr("Delete")
                       }
                       MenuItem {
                           text: qsTr("Select all")
                       }
                       MenuItem {
                           text: qsTr("Invert all")
                       }
                       MenuItem {
                           text: "Settings"
                           onClicked: popup.open()
                       }
                   }
               }

               ToolButton {
                   text: qsTr("View")
                   onClicked: menuView.open()

                   Menu {
                       id: menuView

                       MenuItem {
                           text: qsTr("Toogle full screen")
                       }
                       MenuItem {
                           text: qsTr("Toogle menu bar")
                       }
                       MenuItem {
                           text: qsTr("Font size up")
                       }
                       MenuItem {
                           text: qsTr("Font size down")
                       }
                       MenuItem {
                           text: qsTr("Reset font size")
                       }
                       MenuItem {
                           text: qsTr("Toogle console")
                       }
                       MenuItem {
                           text: qsTr("Toogle property panel")
                       }
                   }
               }

               ToolButton {
                   text: qsTr("Panes")
                   onClicked: menuPanes.open()

                   Menu {
                       id: menuPanes

                       MenuItem {
                           text: qsTr("Split left")
                       }
                       MenuItem {
                           text: qsTr("Split right")
                       }
                       MenuItem {
                           text: qsTr("Split up")
                       }
                       MenuItem {
                           text: qsTr("Split down")
                       }
                       MenuItem {
                           text: qsTr("Next pane")
                       }
                       MenuItem {
                           text: qsTr("Prev pane")
                       }
                   }
               }

               ToolButton {
                   text: qsTr("Tab")
                   onClicked: menuTab.open()

                   Menu {
                       id: menuTab

                       MenuItem {
                           text: qsTr("Next tab")
                       }

                       MenuItem {
                           text: qsTr("Prev tab")
                       }

                       MenuItem {
                           text: qsTr("Close tab")
                       }

                       MenuItem {
                           text: qsTr("History")
                       }
                   }
               }

               ToolButton {
                   text: qsTr("Viewport")
                   onClicked: viewportTab.open()

                   Menu {
                       id: viewportTab

                       MenuItem {
                           text: qsTr("Zoom in")
                       }

                       MenuItem {
                           text: qsTr("Zoom out")
                       }

                       MenuItem {
                           text: qsTr("Move")
                       }

                       MenuItem {
                           text: qsTr("Add node")
                       }

                       MenuItem {
                           text: qsTr("Resize node")
                       }

                       MenuItem {
                           text: qsTr("Format node")
                       }

                       MenuItem {
                           text: qsTr("Collapse node")
                       }

                       MenuItem {
                           text: qsTr("Expand node")
                       }

                       MenuItem {
                           text: qsTr("Open node")
                       }

                       MenuItem {
                           text: qsTr("Open blank node")
                       }

                       MenuItem {
                           text: qsTr("Link")
                       }

                       MenuItem {
                           text: qsTr("Unlink")
                       }
                   }
               }

               ToolButton {
                   text: qsTr("Node")
                   onClicked: nodeTab.open()

                   Menu {
                       id: nodeTab

                       MenuItem {
                           text: qsTr("New node")
                       }

                       MenuItem {
                           text: qsTr("Delete node")
                       }

                       MenuItem {
                           text: qsTr("Import node")
                       }

                       MenuItem {
                           text: qsTr("Export node")
                       }
                   }
               }

               ToolButton {
                   text: qsTr("Run")
                   onClicked: runTab.open()

                   Menu {
                       id: runTab

                       MenuItem {
                           text: qsTr("Build")
                       }

                       MenuItem {
                           text: qsTr("Run")
                       }

                       MenuItem {
                           text: qsTr("Run debug")
                       }

                       MenuItem {
                           text: qsTr("Pause")
                       }

                       MenuItem {
                           text: qsTr("Stop")
                       }
                   }
               }
               ToolButton {
                   text: qsTr("Cloud")
                   onClicked: cloudTab.open()

                   Menu {
                       id: cloudTab

                       MenuItem {
                           text: qsTr("Upload")
                       }

                       MenuItem {
                           text: qsTr("Download")
                       }

                       MenuItem {
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
            y: parent.parent.height / 2 - height / 2
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
