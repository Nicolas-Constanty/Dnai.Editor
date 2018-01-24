import QtQuick 2.4
import QtQuick.Layouts 1.3
import Utils 1.0

import "../Controls"

ColumnLayout {
    id: root
    property bool opened
    property string imgSrc
    property string fullname
    property alias mouseArea: mouseArea
    property alias menu: menu
    property alias profileBtn: profileBtn
    property alias uploadBtn: uploadBtn
    property alias logoutBtn: logoutBtn

    RowLayout {
        anchors.fill: parent
        MouseArea {
            id: mouseArea
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
        }
        Text {
            text: (fullname != "") ? fullname : qsTr("Sign In")
            color: DulySettings.style.text.color
            font.pixelSize: DulySettings.style.font.pixelSize
            font.family: DulySettings.style.font.family
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignRight
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.rightMargin: 10
        }

        Image {
            id: avatar
            source: (imgSrc != "") ? imgSrc : ""
            fillMode: Image.PreserveAspectFit
            sourceSize.width: parent.height
            sourceSize.height: parent.height
        }
    }

    DMenu {
        id: menu
        y: parent.height
        DMenuItem {
            id: profileBtn
            font.pixelSize: DulySettings.style.font.pixelSize
            font.family: DulySettings.style.font.family
            text: qsTr("Profile")
        }
        DMenuItem {
            id: uploadBtn
            font.pixelSize: DulySettings.style.font.pixelSize
            font.family: DulySettings.style.font.family
            text: qsTr("Upload")
        }

        Rectangle {
            border.width: 1
            Layout.fillWidth: true
            height: 1
        }

        DMenuItem {
            id: logoutBtn
            font.pixelSize: DulySettings.style.font.pixelSize
            font.family: DulySettings.style.font.family
            text: qsTr("Logout")
        }
    }
}

