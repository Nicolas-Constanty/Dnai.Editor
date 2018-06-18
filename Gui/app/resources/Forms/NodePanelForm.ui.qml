import QtQuick 2.9
import QtQuick.Controls 2.2

import "../Components"
import "../Panels"

BasePanel {

    property alias intColorRef: intColor
    property alias intBorderColorRef: intBorderColor
    property alias stringColorRef: stringColor
    property alias stringBorderColorRef: stringBorderColor
    property alias boolColorRef: boolColor
    property alias boolBorderColorRef: boolBorderColor
    property alias genericColorRef: genericColor
    property alias genericBorderColorRef: genericBorderColor

    ColorPicker {
        id: fontColor
        name: "FontColor"
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        height: 40
    }
    ColorPicker {
        id: fontColorFaded
        name: "FontColorFaded"
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        height: 40
    }

    ColorPicker {
        id: shadowColor
        name: "ShadowColor"
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        height: 40
    }

    ColorPicker {
        id: connectionColor
        name: "DottedConnectionColor"
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        height: 40
    }

    ColorPicker {
        id: filledConnectionColor
        name: "FilledConnectionColor"
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        height: 40
    }
    ColorPicker {
        id: intColor
        name: "IntColor"
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        height: 40
    }
    ColorPicker {
        id: intBorderColor
        name: "BorderIntColor"
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        height: 40
    }
    ColorPicker {
        id: stringColor
        name: "StringColor"
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        height: 40
    }
    ColorPicker {
        id: stringBorderColor
        name: "BorderStringColor"
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        height: 40
    }
    ColorPicker {
        id: boolColor
        name: "BoolColor"
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        height: 40
    }
    ColorPicker {
        id: boolBorderColor
        name: "BorderBoolColor"
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        height: 40
    }

    ColorPicker {
        id: genericColor
        name: "GenericColor"
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        height: 40
    }
    ColorPicker {
        id: genericBorderColor
        name: "BorderGenericColor"
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        height: 40
    }
}
