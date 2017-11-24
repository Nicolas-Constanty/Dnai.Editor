import QtQuick 2.0
import Utils 1.0

Item {
    property color background: DulySettings.getSettingColor("themes/current/background")
    property color shadowColor: DulySettings.getSettingColor("themes/current/shadowColor")
    property alias border: borderRef
    property Item canvas: canvasRef
    property alias declarationView: declViewRef

    Item {
        id: borderRef
        property color color: DulySettings.getSettingColor("themes/current/border/color")
        width: DulySettings.getSettingNumber("themes/current/border/width")
    }

    Item {
        id: canvasRef
        property color background: DulySettings.getSettingColor("themes/current/Canvas/background")
        property alias grid: gridRef
        Item {
            id: gridRef
            property real step: DulySettings.getSettingNumber("themes/current/Canvas/grid/step")
            property real accentStep: DulySettings.getSettingNumber("themes/current/Canvas/grid/accentStep")
            property color color: DulySettings.getSettingColor("themes/current/Canvas/grid/color")
            property color selectColor: DulySettings.getSettingColor("themes/current/Canvas/grid/selectColor")
            property color accentColor: DulySettings.getSettingColor("themes/current/Canvas/grid/accentColor")
        }
    }
    Item {
        id: nodeRef
        property real borderWidth: DulySettings.getSettingNumber("themes/current/Nodes/borderWidth")
        property alias genericNode: genericRef
        property alias intNode: intRef
        property alias stringNode: stringRef
        property alias boolNode: boolRef
        property alias functionNode: functionRef
        property alias classNode: classRef
        property alias listNode: listRef

        Item {
            id: genericRef
            property Item border: genericBorder
            property color color: DulySettings.getSettingColor("themes/current/Nodes/generic/color")
            Item {
                id: genericBorder
                property color color: DulySettings.getSettingColor("themes/current/Nodes/generic/border/color")
                width: DulySettings.getSettingNumber("themes/current/Nodes/generic/border/width")
            }
        }

        Item {
            id: intRef
            property alias border: intBorder
            property color color: DulySettings.getSettingColor("themes/current/Nodes/int/color")
            Item {
                id: intBorder
                property color color: DulySettings.getSettingColor("themes/current/Nodes/int/border/color")
                width: DulySettings.getSettingNumber("themes/current/Nodes/int/border/width")
            }
        }

        Item {
            id: stringRef
            property alias border: stringBorder
            property color color: DulySettings.getSettingColor("themes/current/Nodes/string/color")
            Item {
                id: stringBorder
                property color color: DulySettings.getSettingColor("themes/current/Nodes/string/border/color")
                width: DulySettings.getSettingNumber("themes/current/Nodes/string/border/width")
            }
        }

        Item {
            id: boolRef
            property alias border: boolBorder
            property color color: DulySettings.getSettingColor("themes/current/Nodes/bool/color")
            Item {
                id: boolBorder
                property color color: DulySettings.getSettingColor("themes/current/Nodes/bool/border/color")
                width: DulySettings.getSettingNumber("themes/current/Nodes/bool/border/width")
            }
        }

        Item {
            id: functionRef
            property alias border: functionBorder
            property color color: DulySettings.getSettingColor("themes/current/Nodes/function/color")
            Item {
                id: functionBorder
                property color color: DulySettings.getSettingColor("themes/current/Nodes/function/border/color")
                width: DulySettings.getSettingNumber("themes/current/Nodes/function/border/width")
            }
        }

        Item {
            id: classRef
            property alias border: classBorder
            property color color: DulySettings.getSettingColor("themes/current/Nodes/class/color")
            Item {
                id: classBorder
                property color color: DulySettings.getSettingColor("themes/current/Nodes/class/border/color")
                width: DulySettings.getSettingNumber("themes/current/Nodes/class/border/width")
            }
        }

        Item {
            id: listRef
            property alias border: listBorder
            property color color: DulySettings.getSettingColor("themes/current/Nodes/list/color")
            Item {
                id: listBorder
                property color color: DulySettings.getSettingColor("themes/current/Nodes/list/border/color")
                width: DulySettings.getSettingNumber("themes/current/Nodes/list/border/width")
            }
        }

        Item {
            id: declViewRef
            property real itemSize: DulySettings.getSettingNumber("themes/current/DeclarationView/itemSize")
            property color background: DulySettings.getSettingColor("themes/current/DeclarationView/background")
            property real radius: DulySettings.getSettingNumber("themes/current/DeclarationView/radius")
            property alias border: declarationBorder
            property alias declContext: declContextRef
            property alias declClass: declClassRef
            property alias declFunction: declFunctionRef
            property alias declVariable: declVariableRef

            Item {
                id: declarationBorder
                property color color: DulySettings.getSettingColor("themes/current/DeclarationView/border/color")
                width: DulySettings.getSettingNumber("themes/current/DeclarationView/border/width")
            }

            Item {
                id: declContextRef
                property real radius: DulySettings.getSettingNumber("themes/current/DeclarationView/Context/radius")
                property color background: DulySettings.getSettingColor("themes/current/DeclarationView/Context/background")
                property alias border : declContextBorder
                Item {
                    id: declContextBorder
                    property color color: DulySettings.getSettingColor("themes/current/DeclarationView/Context/border/color")
                    width: DulySettings.getSettingNumber("themes/current/DeclarationView/Context/border/width")
                }
            }

            Item {
                id: declClassRef
                property real radius: DulySettings.getSettingNumber("themes/current/DeclarationView/Class/radius")
                property color background: DulySettings.getSettingColor("themes/current/DeclarationView/Class/background")
                property alias border : declClassBorder
                Item {
                    id: declClassBorder
                    property color color: DulySettings.getSettingColor("themes/current/DeclarationView/Class/border/color")
                    width: DulySettings.getSettingNumber("themes/current/DeclarationView/Class/border/width")
                }
            }
            Item {
                id: declFunctionRef
                property real radius: DulySettings.getSettingNumber("themes/current/DeclarationView/Function/radius")
                property color background: DulySettings.getSettingColor("themes/current/DeclarationView/Function/background")
                property alias border : delcFunctionBorder
                Item {
                    id: delcFunctionBorder
                    property color color: DulySettings.getSettingColor("themes/current/DeclarationView/Function/border/color")
                    width: DulySettings.getSettingNumber("themes/current/DeclarationView/Function/border/width")
                }
            }
            Item {
                id: declVariableRef
                property real radius: DulySettings.getSettingNumber("themes/current/DeclarationView/Variable/radius")
                property color background: DulySettings.getSettingColor("themes/current/DeclarationView/Variable/background")
                property alias border : declVariableBorder
                Item {
                    id: declVariableBorder
                    property color color: DulySettings.getSettingColor("themes/current/DeclarationView/Variable/border/color")
                    width: DulySettings.getSettingNumber("themes/current/DeclarationView/Variable/border/width")
                }
            }
        }
    }
}
