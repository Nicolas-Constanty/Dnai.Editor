import QtQuick 2.9
import QtQuick.Controls 2.3

import DNAI 1.0
import DNAI.Enums 1.0

import "../JavaScript/CreateComponent.js" as Factory

Menu {
    id: _inputs
    property var getterModel: null
    property var ctItem: null
    property var canvas: null
    Repeater {
        model: _inputs.getterModel
        delegate: Item {
            id: _inputsAction
            Action {
                id: _subMenuInputs
                text: model.name
                Component.onCompleted: {
                    _inputs.addAction(_subMenuInputs)
                }
                onTriggered: {
                    var obj;

                    console.log('model: ', model)
                    console.log('model entity: ', model.entity)
                    console.log('model entity name: ', model.entity.name)
                    console.log('model entity id: ', model.entity.id)

                    console.log('node model: ', nodeModel);

                    Editor.createNode(nodeModel, InstructionID.GETTER, [model.entity.id], canvas.mousePosition.x, canvas.mousePosition.y);

                    /*if (model.varType === 0)
                    {
                        console.log("create Node getter")
                        Factory.createObjects(
                            "resources/Nodes/Getter/IntGetter.qml",
                            { "model" : model, "name" : model.name, "description" : "" })
                        obj = Factory.getObject()
                        Factory.createObjects(
                                    "resources/Components/Node.qml",
                                    { "model": obj, "x": canvas.mousePosition.x, "y": canvas.mousePosition.y },
                                    _inputs.ctItem)
                    }
                    else if (Editor.varTypes.getNameFromValue(model.varType) === "Boolean")
                    {
                        Factory.createObjects(
                            "resources/Nodes/Getter/BoolGetter.qml",
                            { "model" : model, "name" : model.name, "description" : "" })
                        obj = Factory.getObject()
                        Factory.createObjects(
                                    "resources/Components/Node.qml",
                                    { "model": obj, "x": canvas.mousePosition.x, "y": canvas.mousePosition.y },
                                    _inputs.ctItem)
                    }
                    else if (Editor.varTypes.getNameFromValue(model.varType) === "String")
                    {
                        Factory.createObjects(
                            "resources/Nodes/Getter/StringGetter.qml",
                            { "model" : model, "name" : model.name, "description" : "" })
                        obj = Factory.getObject()
                        Factory.createObjects(
                                    "resources/Components/Node.qml",
                                    { "model": obj, "x": canvas.mousePosition.x, "y": canvas.mousePosition.y },
                                    _inputs.ctItem)
                    }*/
                }
            }
        }
    }
}
