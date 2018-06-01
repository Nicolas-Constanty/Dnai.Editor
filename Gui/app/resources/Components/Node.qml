import QtQuick 2.4
import QtQuick.Controls 2.2
import DNAI.Views 1.0
import DNAI 1.0
import DNAI.Enums 1.0

import "../Forms"
import "../Nodes"
import "../Style"

NodeForm {
    property NodeModel model

    id: nodeForm
    inputs: model.inputs
    outputs: model.outputs
    name: model.name
    description: model.description
    icon: model.icon

    state: "Open"
    states: [
        State{
            name: "Open"
            PropertyChanges{ target: nodeForm.headerRef; width: nodeForm.headerRef.implicitWidth }
            PropertyChanges{ target: nodeForm.headerRef; height: nodeForm.headerRef.implicitHeight }
            PropertyChanges{ target: nodeForm.headerRef; radius: 10 }
            PropertyChanges{ target: nodeForm.headerRef; topRight: false }
            PropertyChanges{ target: nodeForm.headerRef; bottomLeft: false }
            PropertyChanges{ target: nodeForm.headerRef; bottomRight: false }
        },
        State{
            name:"Close"
            PropertyChanges{ target: nodeForm.headerRef; width: 60 }
            PropertyChanges{ target: nodeForm.headerRef; height: 60 }
            PropertyChanges{ target: nodeForm.headerRef; radius: 20 }
            PropertyChanges{ target: nodeForm.headerRef; topRight: true }
            PropertyChanges{ target: nodeForm.headerRef; bottomLeft: true }
            PropertyChanges{ target: nodeForm.headerRef; bottomRight: true }
        }
    ]
    transitions: [
        Transition {
            from: "Open"
            to: "Close"

            SequentialAnimation{
                NumberAnimation {
                    target: nodeForm.headerRef
                    property: "width"
                    duration: 200
                    easing.type: Easing.InOutQuad
                }
                NumberAnimation {
                    target: nodeForm.headerRef
                    property: "height"
                    duration: 200
                    easing.type: Easing.InOutQuad
                }
            }
        },
        Transition {
            from: "Close"
            to: "Open"
            SequentialAnimation{
                NumberAnimation {
                    target: nodeForm.headerRef
                    property: "width"
                    duration: 200
                }
                NumberAnimation {
                    target: nodeForm.headerRef
                    property: "height"
                    duration: 200
                    easing.type: Easing.InOutQuad
                }
            }
        }
    ]

    Flow {
        id: _flowIn
        radius: 6
        borderWidth: 3
        antialiasing: true
        x: radius
        y: headerRef.height / 2 - radius - radius / 3
        visible: model.flowIn
        typeFlow: FlowType.Enter
        onLinked: {
            console.log("yooooooooooooooo")
        }

//        Component.onCompleted: {
//            for (var i in _flowIn)
//                console.log(i, _flowIn[i])
//        }
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
                        AppSettings.theme["nodes"]["intNode"]["border"]["color"]
                    else if (t == IOType.String)
                        AppSettings.theme["nodes"]["stringNode"]["border"]["color"]
                    else if (t == IOType.Bool)
                        AppSettings.theme["nodes"]["boolNode"]["border"]["color"]
                    else if (t == IOType.Generic)
                        AppSettings.theme["nodes"]["genericNode"]["border"]["color"]
                }
                fillColor: {
                    if (t == IOType.Int)
                        AppSettings.theme["nodes"]["intNode"]["color"]
                    else if (t == IOType.String)
                        AppSettings.theme["nodes"]["stringNode"]["color"]
                    else if (t == IOType.Bool)
                        AppSettings.theme["nodes"]["boolNode"]["color"]
                    else if (t == IOType.Generic)
                        AppSettings.theme["nodes"]["genericNode"]["color"]
                }
                MLabel {
                    anchors.topMargin: - i.radius / 2
                    anchors.leftMargin: i.radius * 4
                    text: n
                    anchors.left: parent.left
                    anchors.top: parent.top
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
                        AppSettings.theme["nodes"]["intNode"]["border"]["color"]
                    else if (t == IOType.String)
                        AppSettings.theme["nodes"]["stringNode"]["border"]["color"]
                    else if (t == IOType.Bool)
                        AppSettings.theme["nodes"]["boolNode"]["border"]["color"]
                    else if (t == IOType.Generic)
                        AppSettings.theme["nodes"]["genericNode"]["border"]["color"]
                }
                fillColor: {
                    if (t == IOType.Int)
                        AppSettings.theme["nodes"]["intNode"]["color"]
                    else if (t == IOType.String)
                        AppSettings.theme["nodes"]["stringNode"]["color"]
                    else if (t == IOType.Bool)
                        AppSettings.theme["nodes"]["boolNode"]["color"]
                    else if (t == IOType.Generic)
                        AppSettings.theme["nodes"]["genericNode"]["color"]
                }
                MLabel {
                    anchors.topMargin: - o.radius / 2
                    anchors.leftMargin: - o.radius - width
                    text: n
                    anchors.left: parent.left
                    anchors.top: parent.top
                }
            }
        }
    }
}
