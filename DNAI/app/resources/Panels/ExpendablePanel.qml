import QtQuick 2.9
import QtQuick.Controls 2.2
import DNAI 1.0
import QtGraphicalEffects 1.0

import "../Style"

Rectangle {
    id: _panel
    property alias header: _header
    property alias titleobj: _title
    property bool expended: true
    property string title: "Title"
    property alias panel: _panel
    property alias control: _control
    default property alias _contentChildren: _content.data
    property real initialheight: 40

    border.color: AppSettings.style.border.color
    border.width: AppSettings.style.border.width
    color: AppSettings.style.background.darkColor
    clip: true
    Rectangle {
        id: _header
        clip: true
        color: AppSettings.style.background.color
        height: _title.implicitHeight * 1.2
        width: parent.width
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: AppSettings.style.border.width
        anchors.rightMargin: AppSettings.style.border.width
        anchors.topMargin: AppSettings.style.border.width
        TitlePanel {
            id: _title
            text: qsTr(_panel.title)
            horizontalAlignment: Text.AlignLeft
            anchors.left: parent.left
            anchors.leftMargin: 15
            anchors.verticalCenter: parent.verticalCenter
        }
        FontAwesomeTextSolid {
            id: _branch
            text:  "\u2BC6"
            anchors.right: parent.right
            anchors.rightMargin: 15
            anchors.verticalCenterOffset: -2
            anchors.verticalCenter: parent.verticalCenter
        }

        MouseArea {
            id: _control
            property bool selected: false
            anchors.fill: parent
            onClicked: {
                if (selected)
                {
                    if (_panel.state == "Visible")
                        _panel.state = "Invisible"
                    else
                        _panel.state = "Visible"
                }
            }
        }
    }
    Item {
        id: _content
        clip: true
        anchors.top: _header.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: 5
        anchors.leftMargin: AppSettings.style.border.width
        anchors.rightMargin: AppSettings.style.border.width
        anchors.bottomMargin: AppSettings.style.border.width
    }

    states: [
        State{
            name: "Visible"
            PropertyChanges{ target: _panel; height: initialheight }
            PropertyChanges{ target: _branch; rotation: 0 }
        },
        State{
            name:"Invisible"
            PropertyChanges{ target: _panel; height: _header.height + border.width * 2 }
            PropertyChanges{ target: _branch; rotation: 90 }
        }
    ]
    state: "Visible"
    transitions: [
        Transition {
            from: "Visible"
            to: "Invisible"

           NumberAnimation {
               target: _panel
               property: "height"
               duration: 200
               easing.type: Easing.InOutQuad
           }
           NumberAnimation {
               target: _branch
               property: "rotation"
               duration: 200
               easing.type: Easing.InOutQuad
           }
        },
        Transition {
            from: "Invisible"
            to: "Visible"
            NumberAnimation {
               target: _panel
               property: "height"
               duration: 200
               easing.type: Easing.InOutQuad
            }
            NumberAnimation {
               target: _branch
               property: "rotation"
               duration: 200
               easing.type: Easing.InOutQuad
            }
        }
    ]
}
