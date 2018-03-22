import QtQuick 2.4
import DNAI 1.0

import "../Controls"
import "../Components"
import "../Style"

Item {
    id: root
    property bool opened
    property string imgSrc
    property string fullname
    property alias mouseArea: mouseArea
    property alias menu: menu
    property alias profileBtn: profileBtn
    property alias uploadBtn: uploadBtn
    property alias logoutBtn: logoutBtn

    width: height + _text.width

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
    }
    Text {
        id: _text
        text: (fullname != "") ? fullname : qsTr("Sign In")
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        color: AppSettings.style.text.color
        font.pixelSize: AppSettings.style.font.pixelSize
        font.family: AppSettings.style.font.family
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignRight
    }

    Image {
        id: avatar
        anchors.right: parent.right
        anchors.rightMargin: 0
        source: (imgSrc != "") ? imgSrc : ""
        fillMode: Image.PreserveAspectFit
        width: parent.height
        height: parent.height
        sourceSize.width: parent.height
        sourceSize.height: parent.height
        visible: imgSrc != ""
    }

    FontAwesomeTextSolid {
        anchors.right: parent.right
        width: parent.height
        height: parent.height
        text: "\uf2bd"
        font.pointSize: 18
        visible: imgSrc == ""
    }

    DMenu {
        id: menu
        y: parent.height
        DMenuItem {
            id: profileBtn
            text: qsTr("Profile")
        }
        DMenuItem {
            id: uploadBtn
            text: qsTr("Upload")
        }

        Splitter {
        }

        DMenuItem {
            id: logoutBtn
            text: qsTr("Logout")
        }
    }
}
