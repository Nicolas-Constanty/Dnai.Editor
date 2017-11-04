import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.2
import QtQuick.Dialogs 1.2
import CustomGeometry 1.0
import QtGraphicalEffects 1.0

import "Components"
import "Nodes"
import "Nodes/Operator"
import "Nodes/Operator/BinaryOperator"
import "Nodes/Operator/BinaryOperator/Logical"
import "Nodes/Operator/UnaryOperator"

Rectangle {
    id: layout
    property ToolBarHeader toolBarHeader: toolBar
    property ConsoleComponent debugConsole: consoleRef
    property PanelLeft leftPanel: panelLeft
    property PanelRight rightPanel: panelRight

    ToolBarHeader {
        id: toolBar
        width: layout.width
        height: toolBar.heightButton
        anchors.top: layout.top
    }

    DeclarationComponent {
        anchors.top: panelTop.bottom
        anchors.bottom: consoleRef.top
        anchors.left: panelLeft.right
        anchors.right: panelRight.left
    }

    DropShadow {
           anchors.fill: source
           horizontalOffset: -3
           verticalOffset: 3
           radius: 8.0
           samples: 17
           color: "#80000000"
           source: panelTop
    }
    DropShadow {
           anchors.fill: source
           verticalOffset: -3
           radius: 8.0
           samples: 17
           color: "#80000000"
           source: consoleRef
    }
    PanelLeft {
        id: panelLeft;
        anchors.top: toolBar.bottom
        anchors.left: layout.left
        anchors.bottom: consoleRef.top
        width: layout.width / 6;

    }
    PanelRight {
        id: panelRight;
        anchors.top: toolBar.bottom
        anchors.right: layout.right
        anchors.bottom: layout.bottom
        width: layout.width / 6;
        height: root.height - toolBar.height
    }

    DropShadow {
           anchors.fill: source
           horizontalOffset: 3
           verticalOffset: 3
           radius: 8.0
           samples: 17
           color: "#80000000"
           source: panelLeft
    }
    DropShadow {
           anchors.fill: source
           horizontalOffset: -3
           verticalOffset: 3
           radius: 8.0
           samples: 17
           color: "#80000000"
           source: panelRight
    }
    PanelTop {
        id: panelTop
        anchors.top: toolBar.bottom
        anchors.left: panelLeft.right
        anchors.right: panelRight.left
        height: 40
    }

    DropShadow {
           anchors.fill: source
           horizontalOffset: -3
           verticalOffset: 3
           radius: 8.0
           samples: 17
           color: "#80000000"
           source: toolBar
    }
    ConsoleComponent {
        id: consoleRef
        anchors.left: panelLeft.left
        anchors.right: panelRight.left
        height: 200
        state: "Invisible"
        startPos: layout.height - height
    }
}
