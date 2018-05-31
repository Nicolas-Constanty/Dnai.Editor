import QtQuick 2.9
import QtQuick.Controls 2.3

import DNAI.Views 1.0
import DNAI 1.0
import DNAI.Models 1.0

import "../Style"
import "../Nodes"
import "../Nodes/Getter"
import "../Nodes/Operator"
import "../Nodes/Operator/BinaryOperator"
import "../Nodes/Operator/BinaryOperator/Logical"
import "../Nodes/Operator/UnaryOperator"
import "../JavaScript/CreateComponent.js" as Factory

CanvasNode {
    id: canvas
    property var nodeModel: null
    property var entityModel: null
    clip: true
//    anchors.fill: parent
    backgroundColor: AppSettings.theme["canvas"]["background"]
    gridStep: AppSettings.theme["canvas"]["grid"]["step"]
    gridColor: AppSettings.theme["canvas"]["grid"]["color"]
    accentGridStep: AppSettings.theme["canvas"]["grid"]["accentStep"]
    accentGridColor: AppSettings.theme["canvas"]["grid"]["accentColor"]
    states: [
        State {
            when: dragTarget.containsDrag
            PropertyChanges {
                target: canvas
                backgroundColor: AppSettings.theme["canvas"]["grid"]["selectColor"]
            }
        }
    ]
    Item {
        id: content_item
        x: canvas.width/2
        y: canvas.height/2

        Repeater {
            model: entityModel.instructions

        }

        onScaleChanged: {
            zoomText.text = Math.round(content_item.scale * 100) + "%"
        }
    }
    content: content_item

    onContextMenuChanged: {
        _menu.popup()
    }

    Menu {
        id: _menu

        Repeater {
            model: Editor.nodes
            delegate: Item {
                Menu {
                    id: _subMenu
                    title: name
                    Repeater {
                        model: nodeModels
                        delegate: Item {
                            Action {
                                id: _subMenu1
                                text: menuName
                                Component.onCompleted: {
                                    _subMenu.addAction(_subMenu1)
                                }
                                onTriggered: {
                                    Editor.createNode(canvas.nodeModel, item, canvas.mousePosition.x, canvas.mousePosition.y)
                                }
                            }
                        }
                    }
                }
                MenuSeparator {
                    id: _sepMenu
                    visible: Editor.nodes.rowCount() !== index + 1
                }
                Component.onCompleted: {
                    _menu.addMenu(_subMenu)
                    _menu.addItem(_sepMenu)
                }
            }
        }
        Menu {
            id: _getters
            title: "Inputs"
            Repeater {
                //model: canvas.entityModel.inputModels
                model: Editor.entities()
                delegate: Item {
                    id: _getterAction
                    Action {
                        id: _subMenu2
                        text: model.name
                        Component.onCompleted: {
                            _getters.addAction(_subMenu2)
                        }
                        onTriggered: {
                            var obj;
                            if (model.varType === 0)
                            {
                                Factory.createObjects(
                                    "resources/Nodes/Getter/IntGetter.qml",
                                    { "model" : model, "name" : model.name, "description" : "" })
                                obj = Factory.getObject()
                                Factory.createObjects(
                                            "resources/Components/Node.qml",
                                            { "model": obj },
                                            content_item)
                            }
                            else if (model.varType === 1)
                            {
                                Factory.createObjects(
                                    "resources/Nodes/Getter/BoolGetter.qml",
                                    { "model" : model, "name" : model.name, "description" : "" })
                                obj = Factory.getObject()
                                Factory.createObjects(
                                            "resources/Components/Node.qml",
                                            { "model": obj },
                                            content_item)
                            }
                            else if (model.varType === 2)
                            {
                                Factory.createObjects(
                                    "resources/Nodes/Getter/StringGetter.qml",
                                    { "model" : model, "name" : model.name, "description" : "" })
                                obj = Factory.getObject()
                                Factory.createObjects(
                                            "resources/Components/Node.qml",
                                            { "model": obj },
                                            content_item)
                            }
                        }
                    }
                }
            }
        }
        MenuSeparator {
        }
    }

    MLabel {
        id: zoomText
        text: (content_item.scale * 100) + "%"
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 20
    }
}
