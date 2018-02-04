import QtQuick 2.4
import QtQuick.Layouts 1.3
import Utils 1.0

import "../Controls"

ColumnLayout {
    id: root
    property bool connected
    property bool opened
    property string imgSrc
    property string fullname
    property alias mouseArea: mouseArea
    property alias menu: menu
    RowLayout {
        anchors.fill: parent
        MouseArea {
            id: mouseArea
            anchors.fill: parent
        }
        Text {
            text: fullname
            color: DulySettings.style.text.color
            font.pixelSize: DulySettings.style.font.pixelSize
            font.family: DulySettings.style.font.family
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignRight
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Image {
            id: avatar
            source: imgSrc
            fillMode: Image.PreserveAspectFit
            sourceSize.width: parent.height
            sourceSize.height: parent.height
        }
    }

    DMenu {
        id: menu
        y: parent.height
        DMenuItem {
            font.pixelSize: DulySettings.style.font.pixelSize
            font.family: DulySettings.style.font.family
            text: qsTr("Profile")
        }
        DMenuItem {
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
            font.pixelSize: DulySettings.style.font.pixelSize
            font.family: DulySettings.style.font.family
            text: qsTr("Logout")
        }
    }
}

