import QtQuick 2.9
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0

import DNAI 1.0
import Dnai.FontAwesome 1.0

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
    property bool saved: true

    border.color: AppSettings.theme["border"]["color"]
    border.width: AppSettings.theme["border"]["width"]
    color: AppSettings.theme["background"]["darkColor"]
    clip: true
    Rectangle {
        id: _header
        clip: true
        color: AppSettings.theme["background"]["color"]
        height: _title.implicitHeight * 1.2
        width: parent.width
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: AppSettings.theme["border"]["width"]
        anchors.rightMargin: AppSettings.theme["border"]["width"]
        anchors.topMargin: AppSettings.theme["border"]["width"]

        TextAwesomeSolid {
            id: saveId
            text: "\uf192"
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            anchors.leftMargin: 15
            color: saved == true ? AppSettings.theme["background"]["greencolor"] : AppSettings.theme["text"]["errorColor"]

//            anchors.top: parent.top
//            anchors.bottom:
        }

        TitlePanel {
            id: _title
            text: qsTr(_panel.title)
            horizontalAlignment: Text.AlignLeft
      //      anchors.horizontalCenter: parent.horizontalCenter
            anchors.left: saveId.right
            anchors.leftMargin: 15
            anchors.verticalCenter: parent.verticalCenter
        }
        TextAwesomeSolid {
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
        anchors.leftMargin: AppSettings.theme["border"]["width"]
        anchors.rightMargin: AppSettings.theme["border"]["width"]
        anchors.bottomMargin: AppSettings.theme["border"]["width"]
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
