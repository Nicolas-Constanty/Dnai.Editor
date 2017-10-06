import QtQuick 2.4
import QtQuick.Controls 2.2
import CustomGeometry 1.0

GenericNode {
    id: node
    property alias inputs: _inputs.model
    property alias outputs: _outputs.model
    property alias inputDelegate: _inputs.delegate
    property alias outputDelegate: _outputs.delegate
    property alias description: _description.text
    property alias name: _name.text

    content: contentNode
    header: headerNode
    width: headerNode.width
    height: headerNode.height + contentNode.height
    RoundedRectangle {
        id: headerNode
        width: if (_name.width > _description.width)
                   _name.width * 1.5
               else
                   _description.width * 1.5
        height: _name.height * 1.3 + _description.height * 1.3
        bottomLeft: false
        bottomRight: false
        borderWidth: 1
        radius: 10
        borderColor: "#7C7C7C"
        fillColor: "#606060"
        antialiasing: true
        Label {
            id: _name
            text: "Node name"
            anchors.top: parent.top
            anchors.topMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
        Label {
            id: _description
            text: "This is the node description"
            font.italic: true
            anchors.top: parent.top
            anchors.topMargin: _name.height * 1.3
            anchors.horizontalCenter: parent.horizontalCenter
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
    }
    RoundedRectangle {
        id: contentNode
        width: headerNode.width
        height: _inputs.count * 10 + 30
        radius: headerNode.radius
        borderWidth: headerNode.borderWidth
        borderColor: headerNode.borderColor
        fillColor: "#505050"
        antialiasing: headerNode.antialiasing
        topLeft: false
        topRight: false
        y: headerNode.height - headerNode.borderWidth
        ListView {
            id: _inputs
            anchors.topMargin: 10
            anchors.fill: parent
            spacing: 10
            interactive: false
        }
        ListView {
            id: _outputs
            anchors.topMargin: 10
            anchors.fill: parent
            spacing: 10
            interactive: false
        }
    }
}
