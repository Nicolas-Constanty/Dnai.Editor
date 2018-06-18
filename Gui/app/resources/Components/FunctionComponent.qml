import QtQuick 2.9
import QtQuick.Controls 2.2
import CustomGeometry 1.0

import "../Style"

CanvasNode {
    id: canvas
    gridStep: 15
    gridColor: toolBar.menuEditRef.settingRef.themeTabRef.gridColorRef.colorSetting
    accentGridStep: 150
    accentGridColor: toolBar.menuEditRef.settingRef.themeTabRef.accentGridColorRef.colorSetting
    backgroundColor: toolBar.menuEditRef.settingRef.themeTabRef.backgroudColorRef.colorSetting
    MLabel {
        id: zoomText
        text: (canvas.scaleFactor * 100) + "%"
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 20
    }
    onScaleFactorChanged: {
        zoomText.text = Math.round(canvas.scaleFactor * 100) + "%"
    }
}
