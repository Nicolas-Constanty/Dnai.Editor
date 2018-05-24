import QtQuick 2.0
import DNAI 1.0

import "../Style"

FontAwesomeButton {
    id: _control
    property alias decoration: _decoration
    text: "\uf055"
    label.font.pointSize: 12
    label.font.family: "Font Awesome 5 Free Solid"
    label.topPadding: _decoration.implicitHeight / 2
    label.color: _control.hovered ? "#80ffffff" : "#8000000"
    background: Rectangle {
        id: background
        implicitHeight: 30
        color: _control.hovered ?  AppSettings.theme["background"]["darkColor"] : AppSettings.theme["background"]["color"]
        Rectangle {
            id: _decoration
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            implicitHeight: 5
            color: "#00897B"
        }
    }
}
