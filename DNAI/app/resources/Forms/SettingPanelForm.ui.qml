import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import DNAI 1.0

import "../Panels"

Item {
    id: item1
    property alias tabBar: bar
    property alias themeTabRef: themeTab
    property alias nodeTabRef: nodeTab

    TabBar {
        id: bar
        contentWidth: parent.width
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

    StackLayout {
        id: stack
        y: bar.height
        width: parent.width
        height: parent.height - bar.height
        currentIndex: bar.currentIndex

        ThemePanel {
            id: themeTab
        }
        LanguagePanel {
            id: languageTab
        }
        NodePanel {
            id: nodeTab
        }
    }
}
