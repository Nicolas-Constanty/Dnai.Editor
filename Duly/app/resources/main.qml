import QtQuick 2.2
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3
import DNAI.Communication.EventConsumer 1.0
import DNAI 1.0

import "JavaScript/CreateComponent.js" as Factory
import "Layouts"
import "Components"
import "Nodes"
import "Nodes/Operator"
import "Nodes/Operator/BinaryOperator"
import "Nodes/Operator/BinaryOperator/Logical"
import "Nodes/Operator/UnaryOperator"

Item {
    id: rootItem
    property alias appWindow : loader.item
    property double factor : 1.5
    property alias layout: appWindow.baseLayout

    function closeSplashScreen()
    {
        _splashScreen.close()
    }

    SplashScreen {
        id: _splashScreen
    }

    Loader {
        id: loader
        asynchronous: true
        sourceComponent: mainWindow
        opacity: 0
    }

    Component {
        id: mainWindow

        ApplicationWindow {
            id: root
            property BaseLayout baseLayout: undefined
            width: DulySettings.isSettingsLoad() ? 1280 : 400
            height: DulySettings.isSettingsLoad() ? 720 : 150
            minimumHeight: 100
            minimumWidth: 300
            title: qsTr("DNAI")
            color: DulySettings.style.background.color
            visible: false

            Component.onCompleted: {
                DulySettings.init()
                if (DulySettings.isSettingsLoad())
                {
                    Factory.createObjects("resources/Layouts/LayoutClassic.qml", {
                                              "width": root.width,
                                              "height": root.height,
                                              "color": "transparent"
                                          }, root)
                    baseLayout = Factory.getObject()
                    baseLayout.anchors.fill = baseLayout.parent
                }
                else
                {
                    Factory.createObjects("resources/Panels/ChooseThemePanel.qml", {
                                              "width": root.width,
                                              "height": root.height
                                          }, root)
                }
                visible = true
            }

            onVisibleChanged: {
                if (visible == true)
                    _splashScreen.close();
            }
        }
    }
}



