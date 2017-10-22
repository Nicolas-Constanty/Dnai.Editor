import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.2
import QtQuick.Dialogs 1.2
import CustomGeometry 1.0

import "Resources/Components"
import "Resources/Nodes"
import "Resources/Nodes/Operator"
import "Resources/Nodes/Operator/BinaryOperator"
import "Resources/Nodes/Operator/BinaryOperator/Logical"
import "Resources/Nodes/Operator/UnaryOperator"

ApplicationWindow {


    visible: true
    width: 1280
    height: 720
    minimumHeight: 150
    minimumWidth: 300
    title: qsTr("Duly")
    Material.theme: Material.Dark
    Material.accent: Material.color(Material.DeepOrange, Material.Shade400)
    property double factor : 1.5
    id: root
    property ApplicationWindow appWindow : root
    property ToolBarHeader toolBarHeader: toolBar

    header: ToolBarHeader {
        id: toolBar
    }

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onWheel: {
            if (wheel.modifiers & Qt.ControlModifier) {
               canvas.scaleFactor += 0.1 * wheel.angleDelta.y / 120;
            }
        }
        onClicked: {
            if (mouse.button === Qt.RightButton)
            {
                contextMenu.open()
                contextMenu.x = mouseX;
                contextMenu.y = mouseY;
            }
        }
        Menu {
            id: contextMenu
            Label {
                text: "Create node"
                horizontalAlignment: Text.AlignHCenter
            }
            MenuSeparator {}
            MenuItem {
                text: "Operations"
                hoverEnabled: true
                onHoveredChanged: {
                    if (hovered)
                    {
                        ope.open()
                        func.close()
                        if (contextMenu.width + contextMenu.x + ope.width < root.width)
                        {
                            ope.x = contextMenu.width
                        }
                        else if (contextMenu.width + contextMenu.x + ope.width > root.width)
                        {
                            ope.x = -contextMenu.width
                        }
                    }
                }
                Label {
                    text: "►"
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.rightMargin: 15
                }

                Menu {
                    id: ope
                    title: "Operations"
                    MenuItem {
                        id: add
                        text: "Add"
                    }
                    MenuItem {
                        text: "Substract"
                    }
                    MenuItem {
                        text: "Multiply"
                    }
                    MenuItem {
                        text: "Divide"
                    }
                }
            }
            MenuItem {
                text: "Functions"
                hoverEnabled: true
                onHoveredChanged: {
                    if (hovered)
                    {
                        func.open()
                        ope.close()
                        if (contextMenu.width + contextMenu.x + func.width < root.width)
                        {
                            func.x = contextMenu.width
                        }
                        else if (contextMenu.width + contextMenu.x + func.width > root.width)
                        {
                            func.x = -contextMenu.width
                        }
                    }
                }
                Label {
                    text: "►"
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.rightMargin: 15
                }

                Menu {
                    id: func
                    MenuItem {
                        text: "Path finding"
                    }
                    MenuItem {
                        text: "Obstacle detection"
                    }
                    MenuItem {
                        text: "Alpha Go"
                    }
                    MenuItem {
                        text: "Open AI"
                    }
                }
            }
        }
    }

    DulyCanvas {
        id: canvas
        width: root.width
        height: root.height - toolBar.heightButton
        y: toolBar.heightButton
        gridStep: 15
        gridColor: toolBar.menuEditRef.settingRef.themeTabRef.gridColorRef.colorSetting
        accentGridStep: 150
        accentGridColor: toolBar.menuEditRef.settingRef.themeTabRef.accentGridColorRef.colorSetting
        backgroundColor: toolBar.menuEditRef.settingRef.themeTabRef.backgroudColorRef.colorSetting

        Node {
           x: 0
           model: AccessModel {}
        }
        Node {
           x: 0
           y: 100
           model: AddNodeModel {}
        }
        Node {
           x: 0
           y: 200
           model: BinaryAndModel {}
        }
        Node {
           x: 0
           y: 300
           model: BinaryOrModel {}
        }
        Node {
           x: 0
           y: 400
           model: DivideModel {}
        }
        Node {
           x: 0
           y: 500
           model: LeftShiftModel {}
        }

        Node {
           x: 0
           y: 600
           model: ModuloModel {}
        }

        Node {
           x: 0
           y: 700
           model: MultiplicateModel {}
        }
        Node {
           x: 400
           y: 0
           model: RightShiftModel {}
        }
        Node {
           x: 400
           y: 100
           model: SubstractModel {}
        }
        Node {
           x: 400
           y: 200
           model: AndModel {}
        }

        Node {
           x: 400
           y: 300
           model: DifferentModel {}
        }

        Node {
           x: 400
           y: 400
           model: EqualModel {}
        }
        Node {
           x: 400
           y: 500
           model: GreaterEqualModel {}
        }
        Node {
           x: 400
           y: 600
           model: GreaterModel {}
        }
        Node {
           x: 400
           y: 700
           model: EqualModel {}
        }
        Node {
           x: 800
           y: 0
           model: LessEqualModel {}
        }
        Node {
           x: 800
           y: 100
           model: LessModel {}
        }
        Node {
           x: 800
           y: 200
           model: OrModel {}
        }

        Node {
           x: 800
           y: 300
           model: BNotModel {}
        }

        Node {
           x: 800
           y: 400
           model: DecrementModel {}
        }

        Node {
           x: 800
           y: 500
           model: IncrementModel {}
        }
        Node {
           x: 800
           y: 600
           model: NotModel {}
        }
        Node {
           x: 800
           y: 700
           model: ReverseModel {}
        }

        Node {
            x: 1000
            y: 0
            model: XorModel {}
        }
    }
    ConsoleComponent {
        width: parent.width
        height: 200
        y: parent.height - height
    }

}
