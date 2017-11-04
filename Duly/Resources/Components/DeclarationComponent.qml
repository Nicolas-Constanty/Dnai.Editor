import QtQuick 2.9
import QtQuick.Controls 2.2
import CustomGeometry 1.0


import "../Nodes"
import "../Nodes/Operator"
import "../Nodes/Operator/BinaryOperator"
import "../Nodes/Operator/BinaryOperator/Logical"
import "../Nodes/Operator/UnaryOperator"

DulyCanvas {
    id: canvas
    property int margin: 30
    gridStep: 15
    gridColor: toolBar.menuEditRef.settingRef.themeTabRef.gridColorRef.colorSetting
    accentGridStep: 150
    accentGridColor: toolBar.menuEditRef.settingRef.themeTabRef.accentGridColorRef.colorSetting
    backgroundColor: toolBar.menuEditRef.settingRef.themeTabRef.backgroudColorRef.colorSetting

    Node {
        model: AddNodeModel{}
    }
    Node {
        y: 200
        model: AddNodeModel{}
    }
    transformOrigin: Item.Center

//    RoundedRectangle {
//        id:test
//        anchors.top: canvas.top
//        anchors.topMargin: margin
//        anchors.left: canvas.left
//        anchors.leftMargin: margin
//        anchors.right: canvas.right
//        anchors.rightMargin: margin
//        height: 200
//        borderWidth: 10
//        radius: 50
//        borderColor: "#80C8E6C9"
//        fillColor: "#501B5E20"
//        antialiasing: true
//    }
    Rectangle {
        x: parent.width / 2
        y: parent.height / 2
        width: 5
        height: 5
    }

    Label {
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
