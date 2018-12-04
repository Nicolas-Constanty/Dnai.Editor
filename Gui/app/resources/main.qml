import QtQuick 2.2
import QtQuick.Controls 2.2
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3
import DNAI 1.0
import Dnai.Settings 1.0

import "JavaScript/CreateComponent.js" as Factory
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

    SettingParameters {
        id: _settingsParameters
        prefix: "Dnai.Editor_" + Editor.version()
        themePaths: [
            ":/settings/themes/dark.json",
            ":/settings/themes/light.json"
        ]
    }

    Component.onCompleted: {
        AppSettings.parameters = _settingsParameters
        Editor.registerSettings(AppSettings.settings)
        //Load theme 1
        AppSettings.currentTheme = AppSettings.themeNames[0]
    }

    function closeSplashScreen()
    {
        _splashScreen.close()
    }

    function load()
    {
        _loader.active = true;
    }

    SplashScreen {
        id: _splashScreen
    }

    Loader {
        id: _loader
        active: false
        asynchronous: true
        visible: status == Loader.Ready
        sourceComponent: AppSettings.themeLoaded ? _mainWindow : _selectTheme
        onLoaded: {
            _main.hide();
            if (AppSettings.themeLoaded && Editor.solutionName) {
                item.openSolution(Editor.solutionName);
            }
        }
    }

    Component {
        id: _mainWindow

        AppWindow {
            id: appViewMain
            width: 1280
            height: 720
            visible: true
            Component.onCompleted: {
                Editor.registerMainView(appViewMain)
                closeSplashScreen()
            }

            onClosing: {
                _main.close();
            }
        }
    }

    Component {
        id: _selectTheme

        ApplicationWindow {
            id: _cw
            width: 400
            height: 150
            minimumWidth: 400
            minimumHeight: 150
            title: qsTr("DNAI")
            color: AppSettings.theme.colors.background.dark
            visible: true
            ChooseThemePanel {
                id: pane
                Component.onCompleted: {
                    pane.wind = _cw
                    closeSplashScreen()
                }
            }

            onClosing: {
                _main.close();
            }
        }
    }
}



