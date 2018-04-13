import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 2.1
import QtGraphicalEffects 1.0
import "../Style"

Rectangle {
    signal enterToast()
    signal exitToast()
    signal clickToast()

    property string textValue: ""
    property real marginsMore: 10
    property real yMargins: 0
    property string backgroundColor: "#00BFFF"

    x: parent.width - backgroundRect.width + marginsMore + backgroundRect.width
    y: 50 + yMargins
    width: 300
    height: ((textField.font.pixelSize + 5) * textField.lineCount) + 20
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

    MText {
        anchors.fill: parent
        id: textField
        text: textValue
        color: "white"
        font.pointSize: 18
        wrapMode: Text.WordWrap
    }


     MouseArea {
         id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            backgroundRect.opacity = 1.0
            mouseArea.cursorShape = Qt.PointingHandCursor
            backgroundRect.color = backgroundColor
            enterToast()
        }

        onClicked: {
            clickToast()
        }

        onExited: {
            backgroundRect.opacity = 0.75
            mouseArea.cursorShape = Qt.ArrowCursor
            backgroundRect.color =  backgroundColor
            exitToast()
        }
     }

     Component.onCompleted: {
         backgroundRect.x = backgroundRect.x - (marginsMore * 2) - backgroundRect.width
     }
}
