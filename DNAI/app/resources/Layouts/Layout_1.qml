import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
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
    ToolBarHeader {
        id: toolBar
        width: layout.width
        height: toolBar.heightButton
        anchors.top: layout.top
    }

    FunctionComponent {
        anchors.top: pannelTop.bottom
        anchors.bottom: consoleRef.top
        anchors.left: panelLeft.right
        anchors.right: panelRight.left
    }
    ConsoleComponent {
        id: consoleRef
        anchors.left: panelLeft.right
        anchors.right: panelRight.left
        height: 200
        state: "Invisible"
        startPos: layout.height - height
    }
    PanelLeft {
        id: panelLeft;
        anchors.top: toolBar.bottom
        anchors.left: layout.left
        anchors.bottom: layout.bottom
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
        id: pannelTop
        anchors.top: toolBar.bottom
        anchors.left: panelLeft.right
        anchors.right: panelRight.left
        anchors.leftMargin: -1
        anchors.rightMargin: -1
        height: 40
    }
    DropShadow {
           anchors.fill: source
           verticalOffset: -3
           radius: 8.0
           samples: 17
           color: "#80000000"
           source: consoleRef
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
}
