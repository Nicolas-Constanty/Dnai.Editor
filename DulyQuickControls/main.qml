import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.2
import QtQuick.Dialogs 1.2
import QtCharts 2.2
import CustomGeometry 1.0

import "Resources/Components"

ApplicationWindow {
    visible: true
    width: 1280
    height: 720
    minimumHeight: 150
    minimumWidth: 300
    title: qsTr("Dully")
    Material.theme: Material.Dark
    Material.accent: Material.color(Material.DeepOrange, Material.Shade400)
    property double factor : 1.5
    id: root

    header: ToolBarHeader {
        id: toolBar

    }

    DulyCanvas {
        id: canvas
        scale: 1
        anchors.fill: parent
        gridStep: 15
        gridColor: toolBar.menuEditRef.settingRef.themeTabRef.gridColorRef.colorSetting
        accentGridStep: 150
        accentGridColor: toolBar.menuEditRef.settingRef.themeTabRef.accentGridColorRef.colorSetting
        backgroundColor: toolBar.menuEditRef.settingRef.themeTabRef.backgroudColorRef.colorSetting
    }



//    Line {
//        lineWidth: 1
//        p1: Qt.point(10,10)
//        p2: Qt.point(20,20)
//    }

}
