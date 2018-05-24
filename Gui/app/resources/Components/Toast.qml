import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 2.1
import QtGraphicalEffects 1.0

import DNAI 1.0

import "../Style"

Rectangle {
    signal enterToast()
    signal exitToast()
    signal clickToast()
    signal removeToast()

    property string textValue: ""
    property real marginsMore: 10
    property real yMargins: 0
    property string backgroundColor: "#00BFFF"
    property string iconsFont
    property string colorIconsFont
    property bool clickEnable: true
    property string parentWidthUpdate: parent.width

    x: parentWidthUpdate - backgroundRect.width + marginsMore + backgroundRect.width
    y: 50 + yMargins
    width: Qt.platform.os === "windows" ? 300 : 250
    height: ((textField.font.pixelSize + textField.anchors.margins) * textField.lineCount) + 20
    id: backgroundRect
    color: backgroundColor
    radius: 5
    opacity: 0.75

    Behavior on opacity {
            NumberAnimation { duration: 150 }
        }

    Behavior on x {
            NumberAnimation { duration: 300; easing.type: Easing.OutQuad }
        }

    Connections {
        target: parent
        onWidthChanged: {
            backgroundRect.x = backgroundRect.parentWidthUpdate - backgroundRect.width - marginsMore
            backgroundRect.parentWidthUpdate = parent.width
        }
    }


    FontAwesomeTextSolid {
        id: icons
        anchors.verticalCenter: backgroundRect.verticalCenter
        anchors.left: backgroundRect.left
        anchors.margins: 10
        text: iconsFont
        font.pointSize: 20
        color: colorIconsFont
    }

    MText {
     //   anchors.fill: parent
        anchors.left: icons.right
        anchors.right: backgroundRect.right
        anchors.top: backgroundRect.top
        anchors.bottom: backgroundRect.bottom
        horizontalAlignment: Text.AlignJustify
        anchors.margins: 10

        id: textField
        text: textValue
        color: "white"
        font.pointSize: Qt.platform.os === "windows" ? 10 : 14
        wrapMode: Text.WordWrap
    }

     MouseArea {
         id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        enabled: backgroundRect.clickEnable
        onEntered: {
            iconsDelete.visible = true
            backgroundRect.opacity = 1.0
            mouseArea.cursorShape = Qt.PointingHandCursor
            backgroundRect.color = backgroundColor
            enterToast()
        }

        onClicked: {
            clickToast()
        }

        onExited: {
            if (!mouseAreaIconsDelete.isEnter) {
                iconsDelete.visible = false
                backgroundRect.opacity = 0.75
                mouseArea.cursorShape = Qt.ArrowCursor
                backgroundRect.color =  backgroundColor
                exitToast()
            }
        }
     }

     FontAwesomeTextSolid {
         property string crossIconEnter: "\uf057"
         property string crossIconExit: "\uf00d"

         id: iconsDelete
         anchors.top: backgroundRect.top
         anchors.right: backgroundRect.right
         anchors.margins: 5
         text: crossIconExit
         font.pointSize: 12
         color: "white"
         visible: false

         MouseArea {
             id: mouseAreaIconsDelete
             property bool isEnter: false

             anchors.fill: parent
             hoverEnabled: true
             onEntered: {
                 isEnter = true
                 iconsDelete.text = iconsDelete.crossIconEnter
                 mouseAreaIconsDelete.cursorShape = Qt.PointingHandCursor
             }

             onClicked: {
                removeToast()
             }

             onExited: {
                 isEnter = false
                 iconsDelete.text = iconsDelete.crossIconExit
                 mouseAreaIconsDelete.cursorShape = Qt.PointingHandCursor
             }
         }
     }

     Component.onCompleted: {
         backgroundRect.x = backgroundRect.x - (marginsMore * 2) - backgroundRect.width
     }
}
