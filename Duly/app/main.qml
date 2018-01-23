import QtQuick 2.2
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3
import Communication.EventConsumer 1.0
import CustomGeometry 1.0
import Utils 1.0

import "resources/JavaScript/CreateComponent.js" as Factory
import "resources"
import "resources/Layouts"
import "resources/Components"
import "resources/Nodes"
import "resources/Nodes/Operator"
import "resources/Nodes/Operator/BinaryOperator"
import "resources/Nodes/Operator/BinaryOperator/Logical"
import "resources/Nodes/Operator/UnaryOperator"

ApplicationWindow {


    id: root
    property alias appWindow : root
    property double factor : 1.5
    property BaseLayout layout: baseLayout

    BaseLayout {
        id: baseLayout
    }
    visible: true
    width: DulySettings.isSettingsLoad() ? 1280 : 400
    height: DulySettings.isSettingsLoad() ? 720 : 150
    minimumHeight: 100
    minimumWidth: 300
    title: qsTr("DNAI")
    color: DulySettings.style.background.color

    Component.onCompleted: {
        DulySettings.init()
        if (DulySettings.isSettingsLoad())
        {
            Factory.createObjects("resources/Layouts/LayoutClassic.qml", {
                                      "width": root.width,
                                      "height": root.height,
                                      "color": "transparent"
                                  }, root)
            layout = Factory.getObject()
            layout.anchors.fill = layout.parent
        }
        else
        {
            Factory.createObjects("resources/Panels/ChooseThemePanel.qml", {
                                      "width": root.width,
                                      "height": root.height
                                  }, root)
        }
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
