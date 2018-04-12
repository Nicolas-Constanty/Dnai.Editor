import QtQuick 2.2
import QtQuick.Controls 2.2
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3
import DNAI 1.0

import "JavaScript/CreateComponent.js" as Factory
import "Layouts"
import "Views"
import "Nodes"
import "Nodes/Operator"
import "Nodes/Operator/BinaryOperator"
import "Nodes/Operator/BinaryOperator/Logical"
import "Nodes/Operator/UnaryOperator"
import "Panels"

Window {
    id: _main
    visible: true
    modality: Qt.ApplicationModal
    flags: Qt.SplashScreen
    color: "transparent"
    property alias main: _main

    function closeSplashScreen()
    {
        _splashScreen.close()
    }

    function load()
    {
        _loader.active = true;
    }

    function loadMain()
    {
        _loadermain.active = true
    }

    SplashScreen {
        id: _splashScreen
    }

    Loader {
        id: _loadermain
        active: false
        asynchronous: true
        visible: status == Loader.Ready
        sourceComponent: _mainWindow
    }

    Component.onCompleted:
    {
        AppSettings.init()
    }

    Loader {
        id: _loader
        active: false
        asynchronous: true
        visible: status == Loader.Ready
        sourceComponent: AppSettings.isSettingsLoad() ? _mainWindow : _selectTheme
    }

    Component {
        id: _mainWindow

        AppWindow {
            width: 1280
            height: 720
            Component.onCompleted: {
                closeSplashScreen()
                _main.close()
            }
        }
    }

    Component {
        id: _selectTheme

        AppWindow {
            id: _cw
            ChooseThemePanel {
                id: pane
                Component.onCompleted: {
                    console.log("sqdqsdq")
                    pane.wind = _cw
                    closeSplashScreen()
                }
            }
        }
    }
}

//Item {
//    id: rootItem
//    LayoutClassic {

//    }

//    property alias appWindow : loader.item
//    property double factor : 1.5
//    property BaseLayout layout: appWindow.baseLayout

//    function closeSplashScreen()
//    {
//        _splashScreen.close()
//    }



//    Loader {
//        id: loader
//        asynchronous: true
//        sourceComponent: mainWindow
//        opacity: 0
//    }

//    Component {
//        id: mainWindow

//        ApplicationWindow {
//            id: root
//            property BaseLayout baseLayout: undefined
//            width: AppSettings.isSettingsLoad() ? 1280 : 400
//            height: AppSettings.isSettingsLoad() ? 720 : 150
//            minimumHeight: 100
//            minimumWidth: 300
//            title: qsTr("DNAI")
//            color: AppSettings.style.background.color
//            visible: false

//            Component.onCompleted: {
//                AppSettings.init()
//                if (AppSettings.isSettingsLoad())
//                {
//                    Factory.createObjects("resources/Layouts/LayoutClassic.qml", {
//                                              "width": root.width,
//                                              "height": root.height,
//                                              "color": "transparent"
//                                          }, root)
//                    baseLayout = Factory.getObject()
//                    baseLayout.anchors.fill = baseLayout.parent
//                }
//                else
//                {
//                    Factory.createObjects("resources/Panels/ChooseThemePanel.qml", {
//                                              "width": root.width,
//                                              "height": root.height
//                                          }, root)
//                }
//                visible = true
//            }

//            onVisibleChanged: {
//                if (visible == true)
//                    _splashScreen.close();
//            }
//        }
//    }
//}



