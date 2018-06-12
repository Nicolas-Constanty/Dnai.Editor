import QtQuick 2.9
import QtQuick.Controls 2.2
import DNAI.Views 1.0
import DNAI 1.0
import DNAI.Enums 1.0
import Dnai.FontAwesome 1.0

import DNAI.Core 1.0

import "../Forms"
import "../Nodes"
import "../Style"

GenericNode {
    id: _node
    content: contentNode
    header: headerNode
    width: headerNode.width + headerNode.borderWidth * 4
    height: headerNode.height + contentNode.height + headerNode.borderWidth * 6
    property var model: null
    property var instruction_model: null
    property int paddingColumn: 10
    property var function_entity: null

    state: "Open"

    onXChanged: {
        if (instruction_model)
            instruction_model.setX(x)
    }

    onYChanged: {
        if (instruction_model)
            instruction_model.setY(y)
    }

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
            text:  _node.model.name
            anchors.top: parent.top
            anchors.topMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter
            visible: _node.state === "Open"
        }
        MLabel {
            id: _description
            text:  _node.model.description
            font.italic: true
            anchors.top: parent.top
            anchors.topMargin: _name.height * 1.3
            anchors.horizontalCenter: parent.horizontalCenter
            visible: _node.state === "Open"
        }
        TextAwesomeSolid {
            id: _icon
            font.pointSize: 15
            anchors.fill: parent
            visible: _node.state !== "Open"
        }
    }
    RoundedRectangle {
        id: contentNode

        x: borderWidth * 2
        y: borderWidth * 2
        width: headerNode.width
        height: childrenRect.height + 2 * _node.paddingColumn
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
        visible: _node.state === "Open"

        //Flow in list
        Column {
            id: _flowIn
            spacing: 10
            width: 10
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.margins: _node.paddingColumn
            Repeater {
                model: _node.model.flowIn
                delegate: Flow {
                    radius: 6
                    width: 12
                    height: 12
                    borderWidth: 3
                    antialiasing: true
                    typeFlow: FlowType.Enter
                    onLinked: {
                        Controller.Function.instruction.linkExecution(_node.function_entity.id, instructionModel.uid, outindex, _node.instruction_model.uid);
                    }
                    onUnlinked: {
                        Controller.Function.instruction.unlinkExecution(_node.function_entity.id, instructionModel.uid, outindex);
                    }
                }
            }
        }

        //Input list
        Column {
            spacing: 10
            width: 10
            anchors.left: parent.left
            anchors.top: _flowIn.bottom
            anchors.margins: _node.paddingColumn
            Repeater {
                model: _node.model.inputs
                delegate: Input {
                    id: _inputDel
                    property string name: ""
                    width: 10
                    height: 10
                    radius: 5
                    type: 1
                    borderWidth: 3
                    borderColor: {
                            AppSettings.theme["nodes"]["genericNode"]["border"]["color"]
                    }
                    fillColor: {
                            AppSettings.theme["nodes"]["genericNode"]["color"]
                    }
                    onLinked: {
                        Controller.Function.instruction.linkData(_node.function_entity.id, instructionModel.uid, name, _node.instruction_model.uid, _inputDel.name);
                    }
                    onUnlinked: {
                        console.log("Unlink Input")
                        console.log(name)
                        console.log(instructionModel)
                        console.log(_inputDel.name)
                        console.log(_node.instruction_model)
                    }
                    Component.onCompleted: {
                        name = _node.model.inputNames[index]
                    }
                }
            }
        }

        //Flow out List
        Column {
            id: _flowOut
            spacing: 10
            width: 10
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.margins: _node.paddingColumn
            Repeater {
                model: _node.model.flowOut
                delegate: Flow {
                    radius: 6
                    width: 17
                    height: 17
                    borderWidth: 3
                    antialiasing: true
                    typeFlow: FlowType.Exit
                    onLinked: {
                        Controller.Function.instruction.linkExecution(_node.function_entity.id, _node.instruction_model.uid, outindex, instructionModel.uid);
                    }
                    onUnlinked: {
                        Controller.Function.instruction.unlinkExecution(_node.function_entity.id, _node.instruction_model.uid, outindex);
                    }
                }
            }
        }

        //Output List
        Column {
            spacing: 10
            width: 10
            anchors.right: parent.right
            anchors.top: _flowOut.bottom
            anchors.margins: _node.paddingColumn
            Repeater {
                model: _node.model.outputs
                delegate: Output {
                    id: _outputDel
                    property string name: ""
                    width: 10
                    height: 10
                    radius: 5
                    type: 1
                    borderWidth: 3
                    borderColor: {
                            AppSettings.theme["nodes"]["genericNode"]["border"]["color"]
                    }
                    fillColor: {
                            AppSettings.theme["nodes"]["genericNode"]["color"]
                    }
                    onLinked: {
                        Controller.Function.instruction.linkData(_node.function_entity.id, _node.instruction_model.uid, _outputDel.name, instructionModel.uid, name);
                    }
                    onUnlinked: {
                        console.log("Unlink Output")
                        console.log(name)
                        console.log(instructionModel)
                        console.log(_outputDel.name)
                        console.log(_node.instruction_model)
                    }
                    Component.onCompleted: {
                        name = _node.model.outputNames[index]
                    }
                }
            }
        }

    }
}

    //        ListView {
    //            id: _inputs
    //            anchors.topMargin: 10
    //            width: 10
    //            anchors.left: parent.left
    //            spacing: 10
    //            interactive: false
    //            model: _node.model.inputs
    //            Component.onCompleted: {
    //                console.log("Inputs", _node.model.inputs)
    //            }
    //        }
    //        ListView {
    //            id: _outputs
    //            anchors.topMargin: 10
    //            anchors.right: parent.right
    //            spacing: 10
    //            width: 10
    //            interactive: false
    //            model: _node.model.outputs
    //            delegate: Rectangle {
    //                width: 10
    //                height: 10
    //                color: "red"
    //            }
    //        }


//NodeForm {
//    id: nodeForm

//    property var model: null
//    property var instruction_model: null

////    onInstruction_modelChanged: {
////        model.model = instruction_model
////    }

//    inputs: model.inputs
//    outputs: model.outputs
//    name: model.name
//    description: model.description
//    icon: model.icon

//    state: "Open"
//    states: [
//        State{
//            name: "Open"
//            PropertyChanges{ target: nodeForm.headerRef; width: nodeForm.headerRef.implicitWidth }
//            PropertyChanges{ target: nodeForm.headerRef; height: nodeForm.headerRef.implicitHeight }
//            PropertyChanges{ target: nodeForm.headerRef; radius: 10 }
//            PropertyChanges{ target: nodeForm.headerRef; topRight: false }
//            PropertyChanges{ target: nodeForm.headerRef; bottomLeft: false }
//            PropertyChanges{ target: nodeForm.headerRef; bottomRight: false }
//        },
//        State{
//            name:"Close"
//            PropertyChanges{ target: nodeForm.headerRef; width: 60 }
//            PropertyChanges{ target: nodeForm.headerRef; height: 60 }
//            PropertyChanges{ target: nodeForm.headerRef; radius: 20 }
//            PropertyChanges{ target: nodeForm.headerRef; topRight: true }
//            PropertyChanges{ target: nodeForm.headerRef; bottomLeft: true }
//            PropertyChanges{ target: nodeForm.headerRef; bottomRight: true }
//        }
//    ]
//    transitions: [
//        Transition {
//            from: "Open"
//            to: "Close"

//            SequentialAnimation{
//                NumberAnimation {
//                    target: nodeForm.headerRef
//                    property: "width"
//                    duration: 200
//                    easing.type: Easing.InOutQuad
//                }
//                NumberAnimation {
//                    target: nodeForm.headerRef
//                    property: "height"
//                    duration: 200
//                    easing.type: Easing.InOutQuad
//                }
//            }
//        },
//        Transition {
//            from: "Close"
//            to: "Open"
//            SequentialAnimation{
//                NumberAnimation {
//                    target: nodeForm.headerRef
//                    property: "width"
//                    duration: 200
//                }
//                NumberAnimation {
//                    target: nodeForm.headerRef
//                    property: "height"
//                    duration: 200
//                    easing.type: Easing.InOutQuad
//                }
//            }
//        }
//    ]

////    Flow {
////        id: _flowIn
////        radius: 6
////        borderWidth: 3
////        antialiasing: true
////        x: radius
////        y: headerRef.height / 2 - radius - radius / 3
////        visible: model.flowIn
////        typeFlow: FlowType.Enter
////        onLinked: {
////            console.log("Link input")
////        }
////        onUnlinked: {
////            console.log("Unlink input")
////        }
////    }

////    Flow {
////        id: _flowOut
////        radius: 6
////        borderWidth: 3
////        antialiasing: true
////        x: parent.width - radius * 4
////        y: headerRef.height / 2 - radius - radius / 3
////        visible: model.flowOut
////        typeFlow: FlowType.Exit
////        onLinked: {
////            console.log("Link output")
////        }
////        onUnlinked: {
////            console.log("Unlink output")
////        }
////    }

////    flowInItem: _flowIn
////    flowOutItem: _flowOut

////    inputDelegate: Component {
////        Item {
////            width: 10
////            height: 10
////            x: i.radius * 2
////            Input {
////                id: i
////                radius: 5
////                type: nodeForm.model.construction[index]
////                borderWidth: 3
////                borderColor: {
////                    var typename = Editor.propertyPanelProperties.varTypes.getNameFromValue(type)
////                    if (typename === "Integer")
////                        AppSettings.theme["nodes"]["intNode"]["border"]["color"]
////                    else if (typename === "String")
////                        AppSettings.theme["nodes"]["stringNode"]["border"]["color"]
////                    else if (typename === "Boolean")
////                        AppSettings.theme["nodes"]["boolNode"]["border"]["color"]
////                    else
////                        AppSettings.theme["nodes"]["genericNode"]["border"]["color"]
////                }
////                fillColor: {
////                    var typename = Editor.propertyPanelProperties.varTypes.getNameFromValue(type)
////                    if (typename === "Integer")
////                        AppSettings.theme["nodes"]["intNode"]["color"]
////                    else if (typename === "String")
////                        AppSettings.theme["nodes"]["stringNode"]["color"]
////                    else if (typename === "Boolean")
////                        AppSettings.theme["nodes"]["boolNode"]["color"]
////                    else
////                        AppSettings.theme["nodes"]["genericNode"]["color"]
////                }
//////                MLabel {
//////                    anchors.topMargin: - i.radius / 2
//////                    anchors.leftMargin: i.radius * 4
//////                    text: n
//////                    anchors.left: parent.left
//////                    anchors.top: parent.top
//////                }
////            }
////        }
////    }
////    outputDelegate: Component {
////        Item {
////            width: o.width
////            height: o.height
////            x: parent.parent.parent.width - o.radius * 4
////            Output {
////                id: o
////                radius: 5
////                type: nodeForm.model.construction[index]
////                borderWidth: 3
////                borderColor: {
////                    var typename = Editor.propertyPanelProperties.varTypes.getNameFromValue(type)
////                    if (typename === "Integer")
////                        AppSettings.theme["nodes"]["intNode"]["border"]["color"]
////                    else if (typename === "String")
////                        AppSettings.theme["nodes"]["stringNode"]["border"]["color"]
////                    else if (typename === "Boolean")
////                        AppSettings.theme["nodes"]["boolNode"]["border"]["color"]
////                    else
////                        AppSettings.theme["nodes"]["genericNode"]["border"]["color"]
////                }
////                fillColor: {
////                    var typename = Editor.propertyPanelProperties.varTypes.getNameFromValue(type)
////                    if (typename === "Integer")
////                        AppSettings.theme["nodes"]["intNode"]["color"]
////                    else if (typename === "String")
////                        AppSettings.theme["nodes"]["stringNode"]["color"]
////                    else if (typename === "Boolean")
////                        AppSettings.theme["nodes"]["boolNode"]["color"]
////                    else
////                        AppSettings.theme["nodes"]["genericNode"]["color"]
////                }
//////                MLabel {
//////                    anchors.topMargin: - o.radius / 2
//////                    anchors.leftMargin: - o.radius - width
//////                    text: n
//////                    anchors.left: parent.left
//////                    anchors.top: parent.top
//////                }
////            }
////        }
////    }
//}
