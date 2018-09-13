import QtQuick 2.9
import QtQuick.Controls 2.3

import DNAI.Views 1.0
import DNAI 1.0
import DNAI.Models 1.0
import Dnai.Settings 1.0
import Dnai.Controls 1.0
import DNAI.Core 1.0
import Dnai.Theme 1.0

import "../Style"
import "../Nodes"
import "../JavaScript/CreateComponent.js" as Factory

CanvasNode {
    id: canvas
    property var nodeModel
    property var entityModel: nodeModel.guiProperties
    clip: true
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
        property var instuctionNodeMap: ({})
        property int currSize: 0

        function getNodeFrom(guid)
        {
            return content_item.instuctionNodeMap[guid];
        }

        function addNode(func, instr)
        {
            content_item.instuctionNodeMap[instr.guid] = Editor.createNodeQMLComponent(func, instr, content_item);
            console.log("adding node for ", instr.guid, " => ", getNodeFrom(instr.guid));
        }

        function removeNode(instr)
        {
            var qmlNode = getNodeFrom(instr.guid);

            qmlNode.parent = null;
            qmlNode.visible = false;
            qmlNode.clear();
            delete qmlNode;
            delete content_item.instuctionNodeMap[instr.guid];
        }

        onChildrenChanged: {
            if (children.length === 0)
            {
                currSize = 0;
                return;
            }

            var item = children[children.length - 1];

            if (children.length > currSize && item.instruction_model)
            {
                instuctionNodeMap[item.instruction_model.guid] = item;
            }

            currSize = children.length;
        }

        onScaleChanged: {
            zoomText.text = Math.round(content_item.scale * 100) + "%"
        }
    }

    Keys.onDeletePressed: {
        for (var i in content.children)
        {
            var node = content.children[i];

            if (node.selected)
            {
                Controller.Function.removeInstruction(nodeModel.id, node.instruction_model.uid);
            }
        }
    }

    Connections {
        target: Controller.Function.instruction

        onDataLinked: {
            if (func.id === nodeModel.id)
            {
                var nodeFrom = content_item.getNodeFrom(from.guid);
                var nodeTo = content_item.getNodeFrom(to.guid);

                Editor.createIOLink(nodeTo, nodeFrom, func, to, input);
            }
        }

        onDataUnlinked: {
            if (func.id === nodeModel.id)
            {
                Editor.removeIOLink(content_item.getNodeFrom(instruction.guid), instruction, input);
            }
        }

        onExecutionLinked: {
            if (func.id === nodeModel.id)
            {
                var nodeFrom = content_item.getNodeFrom(from.guid);
                var nodeTo = content_item.getNodeFrom(to.guid);

                Editor.createFlowLink(nodeFrom, nodeTo, func, from, outPin, to);
            }
        }
        onExecutionUnlinked: {
            if (func.id === nodeModel.id)
            {
                Editor.removeFlowLink(content_item.getNodeFrom(from.guid), outPin);
            }
        }
    }

    Connections {
        target: Controller.Function

        onEntryPointSet: {
            if (nodeModel.id === func.id)
            {
                Editor.setAsEntryPoint(content_item.getNodeFrom(entry.guid), canvas.entry);
            }
        }

        onInstructionAdded: {
            if (nodeModel.id === func.id)
            {
                content_item.addNode(func, instruction);
            }
        }

        onInstructionRemoved: {
            if (nodeModel.id === func.id)
            {
                content_item.removeNode(instruction);
            }
        }
    }

    content: content_item

    onContextMenuChanged: {
        Editor.updateContextMenuModel(nodeModel)
        _menu2.open()
    }

    function onMenuNodeChoosen(choice)
    {
        if (choice.instructionId !== -1)
        {
            Editor.createNode(
                canvas.nodeModel,
                choice,
                canvas.mousePosition.x - content_item.x,
                canvas.mousePosition.y - content_item.y);
        }
    }

    SearchableMenu {
        id: _menu2
        itemHeight: 30
        itemWidth: 200
        matchViewWidth: 300
        model: Editor.contextMenuModel
        triggeredAction: onMenuNodeChoosen
    }

    Label {
        id: zoomText
        text: (content_item.scale * 100) + "%"
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 20
    }
}
