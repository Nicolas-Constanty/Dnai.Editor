import QtQuick 2.0
import QtQuick.Controls 2.2

import DNAI 1.0
import Dnai.Settings 1.0

Popup {
    property int rootX: 0
    property int rootY: 0

    id: popup
    x: rootX + appWindow.width / 2 - width / 2
    y: rootY + appWindow.height / 2 - height / 2
    background: Rectangle {
        color: AppSettings.theme["modal"]["color"]
        border.width: AppSettings.theme["modal"]["border"]["width"]
        border.color: AppSettings.theme["modal"]["border"]["color"]
    }
    width: 400
    height: 500
    modal: true
    focus: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
}
