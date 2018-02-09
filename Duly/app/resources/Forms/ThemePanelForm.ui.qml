import QtQuick 2.9
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.2

import Utils 1.0

import "../Models"
import "../Components"
import "../Panels"

BasePanel {
    property alias backgroudColorRef: backgroundColor
    property alias gridColorRef: gridColor
    property alias accentGridColorRef: accentGridColor
    property alias themes: chooseTheme

    DropDown {
        id: chooseTheme
        name: "Theme"
        height: 40
    }

    ColorPicker {
        id: backgroundColor
        name: "Background Color"
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        height: 40
    }

    ColorPicker {
        id: gridColor
        name: "Fine Grid Color"
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        height: 40
    }

    ColorPicker {
        id: accentGridColor
        name: "Coarse Grid Color"
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        height: 40
    }
}
