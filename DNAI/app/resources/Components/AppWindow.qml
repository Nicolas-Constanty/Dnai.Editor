import QtQuick 2.0
import QtQuick.Controls 2.2

import DNAI 1.0

import "../Layouts"
import "../JavaScript/CreateComponent.js" as Factory

ApplicationWindow {
    id: _root
    property alias appWindow: _root
    property alias layout: _layout
    width: AppSettings.isSettingsLoad() ? 1280 : 400
    height: AppSettings.isSettingsLoad() ? 720 : 150
    minimumHeight: 150
    minimumWidth: 400
    title: qsTr("DNAI")
    color: AppSettings.style.background.darkColor
    visible: true

    ToolBarHeader {
        id: _toolBar
        height: 40
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
    }
    Item {
        id: _content
        anchors.top: _toolBar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        LayoutClassic {
            id: _layout
        }
    }
}
