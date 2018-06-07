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
        asynchronous: false
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
            id: appViewMain
            width: 1280
            height: 720
            Component.onCompleted: {
                Editor.registerMainView(appViewMain)
                closeSplashScreen()
                _main.close()
            }
        }
    }

    Component {
        id: _selectTheme

        ApplicationWindow {
            id: _cw
            width: AppSettings.isSettingsLoad() ? 1280 : 400
            height: AppSettings.isSettingsLoad() ? 720 : 150
            minimumHeight: 150
            minimumWidth: 400
            title: qsTr("DNAI")
            color: AppSettings.theme["background"]["darkColor"]
            visible: true
            ChooseThemePanel {
                id: pane
                Component.onCompleted: {
                    pane.wind = _cw
                    closeSplashScreen()
                    _main.close()
                }
            }
        }
    }
}



