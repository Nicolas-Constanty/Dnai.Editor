import QtQuick 2.9
import QtQuick.Controls 2.3

import DNAI.Views 1.0
import DNAI 1.0
import DNAI.Models 1.0
import Dnai.Controls 1.0

import "../Style"
import "../Nodes"
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
        Editor.updateContextMenu(nodeModel)
        _menu2.open()
    }

    property var inputs: entityModel.inputModels
    property var outputs: entityModel.outputModels
    property var variables: entityModel.inputModels


    property var inputsMenu: null
    property var outputsMenu: null
    property var variablesMenu: null

    onInputsChanged: {
        if (inputsMenu != null)
            _menu.removeMenu(inputsMenu)
        if (entityModel.inputModels && entityModel.inputModels.rowCount() > 0)
        {
            Factory.createObjects("resources/Components/GetterMenu.qml",
                                  {
                                      "getterModel": entityModel.inputModels,
                                      "title" : "Inputs",
                                      "ctItem": content_item,
                                      "canvas": canvas
                                  }, _menu)
            inputsMenu = Factory.getObject()
            _menu.addMenu(inputsMenu)
        }
    }

    onOutputsChanged: {
        if (outputsMenu != null)
            _menu.removeMenu(outputsMenu)
        if (entityModel.outputModels && entityModel.outputModels.rowCount() > 0)
        {
            Factory.createObjects("resources/Components/GetterMenu.qml",
                                  {
                                      "getterModel": entityModel.outputModels,
                                      "title" : "Outputs",
                                      "ctItem": content_item,
                                      "canvas": canvas
                                  }, _menu)
            outputsMenu = Factory.getObject()
            _menu.addMenu(outputsMenu)
        }
    }

    onVariablesChanged: {
        if (variablesMenu != null)
            _menu.removeMenu(variablesMenu)
        if (Editor.contextMenu.variables && Editor.contextMenu.variables.rowCount() > 0)
        {
            Factory.createObjects("resources/Components/GetterMenu.qml",
                                  {
                                      "getterModel": Editor.contextMenu.variables,
                                      "title" : "Variables",
                                      "ctItem": content_item,
                                      "canvas": canvas
                                  }, _menu)
            variablesMenu = Factory.getObject()
            _menu.addMenu(variablesMenu)
        }
    }

    SearchableMenu {
        id: _menu2
        itemHeight: 30
        itemWidth: 200
        matchViewWidth: 300
        model: Editor.contextMenuModel
//        triggeredAction: displayObj
    }

    Menu {
        id: _menu





//        onOpenedChanged: {
//            if (_menu.opened)
//            {
//                Editor.updateContextMenu(nodeModel)
//


//            }
//        }
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
                                    Editor.createNode(canvas.nodeModel, item.instruction_id, [2, 2, 2], canvas.mousePosition.x, canvas.mousePosition.y)
                                }
                            }
                        }
                    }
                }
                Component.onCompleted: {
                    _menu.addMenu(_subMenu)
                }
            }
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
