import QtQuick 2.4
import QtQuick.Controls 2.2

Item {
    width: if (name.width > description.width)
               name.width * 2
           else
               description.width * 2
    height: 100

    Rectangle {
        id: rectangle
        color: "#99000000"
        radius: 10
        border.width: 1
        anchors.fill: parent
        border.color: "#000000"
        gradient: Gradient {
            GradientStop {
                position: 0.0
                color: "#848484"
            }
            GradientStop {
                position: 1
                color: "#99000000"
            }
        }

        Label {
            id: name
            text: "Node name"
            anchors.top: parent.top
            anchors.topMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            Label {
                id: description
                text: "This is the node description"
                font.italic: true
                anchors.top: parent.top
                anchors.topMargin: name.height
                anchors.horizontalCenter: parent.horizontalCenter
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
        }

        Rectangle {
            height: 1
            color: "#000000"
            width: parent.width - radius * 2
            y: if (description.text != "")
                   parent.radius + name.height + description.height
               else
                   parent.radius + name.height
            x: radius
        }
    }
}
