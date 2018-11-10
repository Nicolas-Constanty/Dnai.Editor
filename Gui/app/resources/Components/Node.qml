import QtQuick 2.9
import QtQuick.Controls 2.2
import DNAI.Views 1.0

import DNAI 1.0
import DNAI.Enums 1.0
import Dnai.FontAwesome 1.0
import Dnai.Settings 1.0
import Dnai.Theme 1.0

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

    function stringToColor(str)
    {
        var hash = 0;
        for (var i = 0; i < str.length; i++) {
            hash = str.charCodeAt(i) + ((hash << 5) - hash);
        }
        var colour = '#';
        for (var c = 0; c < 3; c++) {
            var value = (hash >> (c * 8)) & 0xFF;
            colour += ('00' + value.toString(16)).substr(-2);
        }
        return Qt.lighter(colour);
    }

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
        id: headerNode

        x: borderWidth * 2
        y: borderWidth * 2

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

        Label {
            id: _name
            text:  _node.model.name
            anchors.top: parent.top
            anchors.topMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter
            visible: _node.state === "Open"
        }
        Label {
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

        anchors.top: headerNode.bottom
        anchors.topMargin: headerNode.borderWidth + 1

        visible: _node.state === "Open"

        radius: headerNode.radius
        borderWidth: headerNode.borderWidth
        borderColor: headerNode.borderColor
        fillColor: "#aa000000"
        antialiasing: headerNode.antialiasing
        topLeft: false
        topRight: false
        bottomLeft: false

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
                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        propagateComposedEvents: true
                        onContainsMouseChanged: {
                            isHover = containsMouse
                        }
                        onPressed: {
                            mouse.accepted = false
                        }
                    }
                    radius: 6
                    width: 12
                    height: 12
                    borderWidth: 3
                    antialiasing: true
                    typeFlow: FlowType.Enter
                    curveColor: AppSettings.theme["flow"]["outer"]
                    borderColor: isHover ? AppSettings.theme["flow"]["inner"] : AppSettings.theme["flow"]["outer"]
                    fillColor: isLink || isHover ? AppSettings.theme["flow"]["outer"] : AppSettings.theme["flow"]["inner"]
                    onLinked: {
                        if (instructionModel)
                            Controller.Function.instruction.linkExecution(_node.function_entity.id, instructionModel.uid, outindex, _node.instruction_model.uid);
                        else
                            Controller.Function.setEntryPoint(_node.function_entity.id, _node.instruction_model.uid);
                    }
                    onUnlinked: {
                        if (instructionModel)
                            Controller.Function.instruction.unlinkExecution(_node.function_entity.id, instructionModel.uid, outindex);
                        else
                            console.log("Unset entry point");
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
                model: _node.model.inputSize
                delegate: Input {
                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        propagateComposedEvents: true
                        onContainsMouseChanged: {
                            isHover = containsMouse
                        }
                        onPressed: {
                            mouse.accepted = false
                        }
                    }
                    id: _inputDel
                    property string name: ""
                    property string innerColor: "black"
                    property string outerColor: "black"

                    width: 10
                    height: 10
                    radius: 5
                    borderWidth: 3
                    curveColor: outerColor
                    borderColor: isHover ? innerColor : outerColor
                    fillColor: isLink || isHover ? outerColor : innerColor
                    onLinked: {
                        if (_node.instruction_model.getInputType(_inputDel.name) === '{0db5b2f0-38d0-8f54-9433-479d1d90a699}'
                            || instructionModel.getOutputType(name) === '{0db5b2f0-38d0-8f54-9433-479d1d90a699}'
                            || instructionModel.getOutputType(name) === _node.instruction_model.getInputType(_inputDel.name))
                        {
                            Controller.Function.instruction.linkData(_node.function_entity.id, instructionModel.uid, name, _node.instruction_model.uid, _inputDel.name);
                        }
                    }
                    onUnlinked: {
                        Controller.Function.instruction.unlinkData(_node.function_entity.id, _node.instruction_model.uid, _inputDel.name);
                    }
                    Component.onCompleted: {
                        name = _node.model.inputNames[index]
                        var inpType = Controller.getEntityGui(_node.instruction_model.getInputType(name));
                        var generatedColor = _node.stringToColor(inpType.guid + "");

                        if (inpType.id <= 5)
                        {
                            innerColor = AppSettings.theme["types"][inpType.name]["inner"];
                            outerColor = AppSettings.theme["types"][inpType.name]["outer"];
                        }
                        else
                        {
                            innerColor = "black";
                            outerColor = generatedColor;
                        }
                    }

                    Text {
                        id: _inputName

                        anchors.left: parent.right
                        anchors.leftMargin: 5
                        height: parent.height

                        text: _node.model.getInputDisplayName(parent.name)
                        font.pointSize: 8

                        color: "white"
                    }

                    TextField {
                        id: _inputValue

                        //visible: parent.type >= 1 && parent.type <= 5

                        anchors.left: _inputName.right
                        anchors.leftMargin: 5
                        padding: 0
                        width: 50
                        height: parent.height

                        text: ""
                        placeholderText: ""
                        font.pointSize: 6
                        enableBar: false

                        Component.onCompleted: {
                            _inputValue.text = _node.instruction_model.getInputValue(_inputDel.name);
                        }

                        onAccepted: {
                            if (_inputValue.text)
                                Controller.Function.instruction.setInputValue(_node.function_entity.id, _node.instruction_model.uid, _inputDel.name, _inputValue.text);
                        }
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
                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        propagateComposedEvents: true
                        onContainsMouseChanged: {
                            isHover = containsMouse
                        }
                        onPressed: {
                            mouse.accepted = false
                        }
                    }
                    radius: 6
                    width: 17
                    height: 17
                    borderWidth: 3
                    antialiasing: true
                    typeFlow: FlowType.Exit
                    curveColor: AppSettings.theme["flow"]["outer"]
                    borderColor: isHover ? AppSettings.theme["flow"]["inner"] : AppSettings.theme["flow"]["outer"]
                    fillColor: isLink || isHover ? AppSettings.theme["flow"]["outer"] : AppSettings.theme["flow"]["inner"]
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
                model: _node.model.outputSize
                delegate: Output {
                    id: _outputDel
                    property string name: ""
                    property string innerColor : "black"
                    property string outerColor : "black"

                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        propagateComposedEvents: true
                        onContainsMouseChanged: {
                            isHover = containsMouse
                        }
                        onPressed: {
                            mouse.accepted = false
                        }
                    }

                    width: 10
                    height: 10
                    radius: 5
                    borderWidth: 3
                    curveColor: outerColor
                    borderColor: isHover ? innerColor : outerColor
                    fillColor: isLink || isHover ? outerColor : innerColor
                    onLinked: {
                        if (_node.instruction_model.getInputType(_inputDel.name) === '{0db5b2f0-38d0-8f54-9433-479d1d90a699}'
                            || instructionModel.getOutputType(name) === '{0db5b2f0-38d0-8f54-9433-479d1d90a699}'
                            || _node.instruction_model.getOutputType(_outputDel.name) === instructionModel.getInputType(name))
                        {
                            console.log('in type: ', instructionModel.getInputType(name), ' vs out type: ', _node.instruction_model.getOutputType(_outputDel.name));
                            Controller.Function.instruction.linkData(_node.function_entity.id, _node.instruction_model.uid, _outputDel.name, instructionModel.uid, name);
                        }
                    }
                    onUnlinked: {
                        Controller.Function.instruction.unlinkData(_node.function_entity.id, instruction_model.id, name);
                    }
                    Component.onCompleted: {
                        name = _node.model.outputNames[index]
                        var oupType = Controller.getEntityGui(_node.instruction_model.getOutputType(name));
                        var generatedColor = _node.stringToColor(oupType.guid + "");

                        if (oupType.id <= 5)
                        {
                            innerColor = AppSettings.theme["types"][oupType.name]["inner"];
                            outerColor = AppSettings.theme["types"][oupType.name]["outer"];
                        }
                        else
                        {
                            innerColor = "black";
                            outerColor = generatedColor;
                        }
                    }

                    Text {
                        id: _outputName

                        anchors.right: parent.left
                        anchors.rightMargin: 5
                        height: parent.height

                        text: _node.model.getOutputDisplayName(parent.name)
                        font.pointSize: 8

                        color: "white"
                    }
                }
            }
        }

    }
}
