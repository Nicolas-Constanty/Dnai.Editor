import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.2
import QtQuick.Dialogs 1.2
import CustomGeometry 1.0
import QtGraphicalEffects 1.0
import Communication.EventConsumer 1.0


import "resources"
import "resources/Components"
import "resources/Nodes"
import "resources/Nodes/Operator"
import "resources/Nodes/Operator/BinaryOperator"
import "resources/Nodes/Operator/BinaryOperator/Logical"
import "resources/Nodes/Operator/UnaryOperator"

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
    property ToolBarHeader toolBarHeader: layout.toolBarHeader
    property ConsoleComponent debugConsole: layout.debugConsole
    property alias layoutRef: layout

//    Layout_1 {
//        id: layout
//        width: parent.width
//        height: parent.height
//        color: "transparent"
//    }

    LayoutClassic {
        id: layout
        width: parent.width
        height: parent.height
        color: "transparent"
    }

/*   EventConsumer {
        clientName: "Duly GUI"
        description: "F1D1S1L1C1"
        eventName: "TOTO"

        onReceiveEvent: {
            console.log(data[1])
        }
    }

    EventConsumer {
        clientName: "Duly GUI"
        description: "C1"
        eventName: "TITI"

        onReceiveEvent: {
            console.log(data)
        }
    }*/
}
