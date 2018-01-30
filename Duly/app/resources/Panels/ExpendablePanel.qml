import QtQuick 2.9
import QtQuick.Controls 2.2
import Utils 1.0

import "../Style"

Rectangle {
    id: _panel
    property alias header: _header
    property bool expended: true
    property string title: Title
    property alias panel: _panel
    default property alias _contentChildren: _content.data

    border.color: DulySettings.style.border.color
    border.width: DulySettings.style.border.width
    color: DulySettings.style.background.darkColor
    Rectangle {
        id: _header
        color: DulySettings.style.background.color
        height: _title.implicitHeight * 1.2
        width: parent.width
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: DulySettings.style.border.width
        anchors.rightMargin: DulySettings.style.border.width
        anchors.topMargin: DulySettings.style.border.width
        TitlePanel {
            id: _title
            text: qsTr(_panel.title)
            horizontalAlignment: Text.AlignLeft
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.right: control.left
        }
        MButton {
            id: control
            text: _panel.state == "Visible" ? "\u2BC6" : "\u2BC7"
            anchors.right: parent.right
            anchors.rightMargin: 5
            anchors.top: _header.top
            anchors.bottom: _header.bottom
            background: Rectangle {
                anchors.bottom: parent.bottom
                anchors.top: parent.top
                color: control.pressed ? DulySettings.style.background.darkColor : control.hovered ? DulySettings.style.background.lightColor : DulySettings.style.background.color
            }
            onClicked: {
                if (_panel.state == "Visible")
                    _panel.state = "Invisible"
                else
                    _panel.state = "Visible"
            }
        }
    }
    Item {
        id: _content
        anchors.top: _header.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: DulySettings.style.border.width
        anchors.rightMargin: DulySettings.style.border.width
        anchors.bottomMargin: DulySettings.style.border.width
    }

    states: [
        State{
            name: "Visible"
            PropertyChanges{ target: _panel; height: (parent.height - 6 * (parent.children.length -1)) / (parent.children.length) }
        },
        State{
            name:"Invisible"
            PropertyChanges{ target: _panel; height: _header.height + border.width * 2 }
        }
    ]
    state: "Visible"
    transitions: [
        Transition {
            from: "Visible"
            to: "Invisible"

            SequentialAnimation{
               NumberAnimation {
                   target: _panel
                   property: "height"
                   duration: 500
                   easing.type: Easing.InOutQuad
               }
            }
        },
        Transition {
            from: "Invisible"
            to: "Visible"
            SequentialAnimation{
               NumberAnimation {
                   target: _panel
                   property: "height"
                   duration: 500
                   easing.type: Easing.InOutQuad
               }
            }
        }
    ]
}
