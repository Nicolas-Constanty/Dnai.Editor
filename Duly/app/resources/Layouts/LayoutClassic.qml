import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import QtGraphicalEffects 1.0

import DNAI 1.0
import DNAI.Views 1.0

import "../Style"
import "../Components"
import "../Panels"
import "../Models"
import "../JavaScript/CreateComponent.js" as Factory

BaseLayout {
    id: layout
    toolBarHeader: toolBar
    debugConsole: consoleRef
    leftPanel: panelLeft
    rightPanel: panelRight
//    topPanel: panelTop
//    PanelTop {
//        id: panelTop
//        anchors.left: parent.left
//        anchors.right: parent.right
//        height: 24
//        border.width: 0
//    }
    function appendTab(type, name)
    {
        if (type === 0)
        {
            Factory.createObjects("resources/Panels/PanelTop.qml", {
                                      "height": 24
                                  }, _stack)
            var mobj = Factory.getObject()
            console.log(mobj)
            mobj.anchors.left = mobj.parent.left
            mobj.anchors.right = mobj.parent.right
            mobj.border.width = 0
            Factory.createObjects("resources/Components/TabButtonRounded.qml", {
                                      "text": name,
                                      "implicitHeight": 20,
                                      "stack": _stack,
                                      "refContent": mobj,
                                      "refTabBar": bar
                                  }, bar)
            var tabButton = Factory.getObject();
            console.log(tabButton)
            bar.addItem(tabButton)
            _stack.push(mobj)
        }
    }

    Component.onCompleted: {
        appendTab(0, "hello")
        appendTab(0, "yoooooooooooo")
    }

    ToolBarHeader {
        id: toolBar
        width: layout.width
        height: 40
        anchors.top: layout.top
    }

    TabBar {
        id: bar
        anchors.top: toolBar.bottom
        anchors.left: panelLeft.right
        anchors.leftMargin: -1
        anchors.right: panelRight.left
        anchors.rightMargin: -1
        implicitHeight: 20

//        TabButtonRounded {
//            text: qsTr("Home")
//            implicitHeight: 20
//        }

        background: Rectangle {
             color: DulySettings.style.background.darkColor
             Rectangle {
                 anchors.bottom: parent.bottom
                 anchors.topMargin: 20
                 anchors.left: parent.left
                 anchors.right: parent.right
                 height: 1
                 color: DulySettings.style.border.color
             }
        }
    }

    StackView {
        id: _stack
        anchors.top: bar.bottom
        anchors.bottom: consoleRef.top
        anchors.left: panelLeft.right
        anchors.right: panelRight.left
    }

    Rectangle {
        anchors.top: bar.bottom
        anchors.topMargin: 24
        anchors.left: panelLeft.right
        anchors.leftMargin: -1
        anchors.right: panelRight.left
        anchors.rightMargin: -1
        height: 1
        color: DulySettings.style.border.color
    }
//    DeclarationView {
//        anchors.top: panelTop.bottom
//        anchors.bottom: consoleRef.top
//        anchors.left: panelLeft.right
//        anchors.right: panelRight.left
//    }

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

//    DropShadow {
//           anchors.fill: source
//           horizontalOffset: -3
//           verticalOffset: 3
//           radius: 8.0
//           samples: 17
//           color: "#80000000"
//           source: toolBar
//    }
    ConsoleComponent {
        id: consoleRef
        anchors.left: toolBar.left
        anchors.right: panelRight.left
        height: 200
        state: "Invisible"
        startPos: layout.height - height
    }
}
