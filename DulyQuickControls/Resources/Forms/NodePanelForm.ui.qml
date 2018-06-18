import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "../Components"

Item {

    property alias colRef: column
    property alias rectRef: rectangle

    property alias intColorRef: intColor
    property alias intBorderColorRef: intBorderColor
    property alias stringColorRef: stringColor
    property alias stringBorderColorRef: stringBorderColor
    property alias boolColorRef: boolColor
    property alias boolBorderColorRef: boolBorderColor

    ScrollView {
        id: rectangle
        anchors.rightMargin: 20
        anchors.leftMargin: 20
        anchors.bottomMargin: 20
        anchors.topMargin: 50
        anchors.fill: parent

        ColumnLayout {
            id: column
            spacing: 0
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
        }
    }
}
