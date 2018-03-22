import QtQuick 2.4
import QtQuick.Controls 2.2
import DNAI.Views 1.0
import DNAI 1.0

import "../Style"

GenericNode {
    id: node
    property alias inputs: _inputs.model
    property alias outputs: _outputs.model
    property alias inputDelegate: _inputs.delegate
    property alias outputDelegate: _outputs.delegate
    property alias description: _description.text
    property alias name: _name.text
    property alias flowIn: node.flowIn
    property alias flowOut: node.flowOut
    property alias headerRef: headerNode
    property alias icon: _icon.text

    content: contentNode
    header: headerNode
    width: headerNode.width + headerNode.borderWidth * 4
    height: headerNode.height + contentNode.height + headerNode.borderWidth * 6
    RoundedRectangle {
        x: borderWidth * 2
        y: borderWidth * 2
        id: headerNode
        implicitWidth: if (_name.width > _description.width
                               && _name.width * 1.5 > 100)
                           _name.width * 1.5
                       else if (_description.width * 1.5 > 200)
                           _description.width * 1.5
                       else
                           200
        implicitHeight: _name.height * 1.3 + _description.height * 1.3
        bottomLeft: false
        bottomRight: false
        topRight: false
        borderWidth: 1
        radius: 10
        borderColor: "#7C7C7C"
        fillColor: "#aa101010"
        antialiasing: true
        MLabel {
            id: _name
            text: "Node name"
            anchors.top: parent.top
            anchors.topMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter
            visible: node.state === "Open"
        }
        MLabel {
            id: _description
            text: "This is the node description"
            font.italic: true
            anchors.top: parent.top
            anchors.topMargin: _name.height * 1.3
            anchors.horizontalCenter: parent.horizontalCenter
            visible: node.state === "Open"
        }
        FontAwesomeTextSolid {
            id: _icon
            font.pointSize: 15
            anchors.fill: parent
            visible: node.state !== "Open"
        }
    }
    RoundedRectangle {
        id: contentNode

        x: borderWidth * 2
        y: borderWidth * 2
        width: headerNode.width
        height: _inputs.count * 10 + 30
        radius: headerNode.radius
        borderWidth: headerNode.borderWidth
        borderColor: headerNode.borderColor
        fillColor: "#aa000000"
        antialiasing: headerNode.antialiasing
        topLeft: false
        topRight: false
        bottomLeft: false
        anchors.top: headerNode.bottom
        anchors.topMargin: headerNode.borderWidth + 1
        visible: node.state === "Open"
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
