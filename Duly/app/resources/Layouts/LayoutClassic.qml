import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import CustomGeometry 1.0
import QtGraphicalEffects 1.0

import "../Components"
import "../Panels"
import "../Models"

BaseLayout {
    id: layout
    toolBarHeader: toolBar
    debugConsole: consoleRef
    leftPanel: panelLeft
    rightPanel: panelRight
    topPanel: panelTop

    ToolBarHeader {
        id: toolBar
        width: layout.width
        height: 40
        anchors.top: layout.top
    }

    DeclarationView1 {
        anchors.top: panelTop.bottom
        anchors.bottom: consoleRef.top
        anchors.left: panelLeft.right
        anchors.right: panelRight.left
    }

//    NodeCanvas {
//        anchors.top: panelTop.bottom
//        anchors.bottom: consoleRef.top
//        anchors.left: panelLeft.right
//        anchors.right: panelRight.left
//    }

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
        height: appWindow.height - toolBar.height
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
        anchors.leftMargin: -1
        anchors.right: panelRight.left
        anchors.rightMargin: -1
        height: 24
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
        anchors.left: toolBar.left
        anchors.right: panelRight.left
        height: 200
        state: "Invisible"
        startPos: layout.height - height
    }
}
