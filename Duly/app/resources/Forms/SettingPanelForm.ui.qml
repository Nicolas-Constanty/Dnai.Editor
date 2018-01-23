import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import Utils 1.0

import "../Panels"

Item {
    id: item1
    property alias tabBar: bar
    property alias themeTabRef: themeTab
    property alias nodeTabRef: nodeTab

    StackLayout {
        id: stack
        currentIndex: bar.currentIndex
        anchors.fill: parent

        ThemePanel {
            id: themeTab
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        LanguagePanel {
            id: languageTab
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        NodePanel {
            id: nodeTab
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }

    TabBar {
        id: bar
        background: Rectangle {
            color: DulySettings.style.background.color
        }
        TabButton {
            text: qsTr("Theme")
        }
        TabButton {
            text: qsTr("Languages")
        }
        TabButton {
            text: qsTr("Node apparence")
        }
    }
}
