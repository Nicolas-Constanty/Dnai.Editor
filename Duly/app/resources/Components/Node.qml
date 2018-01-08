import QtQuick 2.4
import QtQuick.Controls 2.2
import CustomGeometry 1.0
import CustomViews 1.0
import Utils 1.0

import "../Forms"
import "../Nodes"

NodeForm {
    property NodeModel model

    id: nodeForm
    inputs: model.inputs
    outputs: model.outputs
    name: model.name
    description: model.description

    Flow {
        id: _flowIn
        radius: 6
        borderWidth: 3
        antialiasing: true
        x: radius
        y: headerRef.height / 2 - radius - radius / 3
        visible: model.flowIn
        typeFlow: FlowType.Enter
    }

    Flow {
        id: _flowOut
        radius: 6
        borderWidth: 3
        antialiasing: true
        x: parent.width - radius * 4
        y: headerRef.height / 2 - radius - radius / 3
        visible: model.flowOut
        typeFlow: FlowType.Exit
    }

    flowInItem: _flowIn
    flowOutItem: _flowOut

    inputDelegate: Component {
        Item {
            width: 10
            height: 10
            x: i.radius * 2
            Input {
                id: i
                radius: 5
                type: t
                borderWidth: 3
                borderColor: {
                    if (t == IOType.Int)
                        DulySettings.style.nodes.intNode.border.color
                    else if (t == IOType.String)
                        DulySettings.style.nodes.stringNode.border.color
                    else if (t == IOType.Bool)
                        DulySettings.style.nodes.boolNode.border.color
                    else if (t == IOType.Generic)
                        DulySettings.style.nodes.genericNode.border.color
                }
                fillColor: {
                    if (t == IOType.Int)
                        DulySettings.style.nodes.intNode.color
                    else if (t == IOType.String)
                        DulySettings.style.nodes.stringNode.color
                    else if (t == IOType.Bool)
                        DulySettings.style.nodes.boolNode.color
                    else if (t == IOType.Generic)
                        DulySettings.style.nodes.genericNode.color
                }
                Label {
                    anchors.topMargin: - i.radius / 2
                    anchors.leftMargin: i.radius * 4
                    text: n
                    anchors.left: parent.left
                    anchors.top: parent.top
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    color: DulySettings.style.text.color
                    font.family: DulySettings.style.font.family
                    font.pixelSize: DulySettings.style.font.pixelSize
                }
            }
        }

    }
    outputDelegate: Component {
        Item {
            width: o.width
            height: o.height
            x: parent.parent.parent.width - o.radius * 4
            Output {
                id: o
                radius: 5
                type: t
                borderWidth: 3
                borderColor: {
                    if (t == IOType.Int)
                        DulySettings.style.nodes.intNode.border.color
                    else if (t == IOType.String)
                        DulySettings.style.nodes.stringNode.border.color
                    else if (t == IOType.Bool)
                        DulySettings.style.nodes.boolNode.border.color
                    else if (t == IOType.Generic)
                        DulySettings.style.nodes.genericNode.border.color
                }
                fillColor: {
                    if (t == IOType.Int)
                        DulySettings.style.nodes.intNode.color
                    else if (t == IOType.String)
                        DulySettings.style.nodes.stringNode.color
                    else if (t == IOType.Bool)
                        DulySettings.style.nodes.boolNode.color
                    else if (t == IOType.Generic)
                        DulySettings.style.nodes.genericNode.color
                }
                Label {
                    anchors.topMargin: - o.radius / 2
                    anchors.leftMargin: - o.radius - width
                    text: n
                    anchors.left: parent.left
                    anchors.top: parent.top
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    color: DulySettings.style.text.color
                    font.family: DulySettings.style.font.family
                    font.pixelSize: DulySettings.style.font.pixelSize
                }
            }
        }
    }
}
