import QtQuick 2.9
import QtQuick.Controls 2.3

import DNAI.Views 1.0
import DNAI 1.0
import DNAI.Models 1.0
import Dnai.Settings 1.0
import Dnai.Controls 1.0
import DNAI.Core 1.0

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

        onScaleChanged: {
            zoomText.text = Math.round(content_item.scale * 100) + "%"
        }

        onChildrenChanged: {
            console.log("==C==");
            for (var child in children)
            {
                console.log("Child ", child, ": ", children[child]);
            }
            console.log("=====");
        }

        Connections {
            target: Controller.Function.instruction

            onDataLinked: {
                console.log("data linked in func ", func.name, ": ", from.uid, '(', output, ')->', to.uid, '(', input, ')');
            }
            onDataUnlinked: {
                console.log("data unlinked in func ", func.name, ': ', instruction.uid, '(', input ,')')
            }
            onExecutionLinked: {
                console.log("flow linked in func ", func.name, ': ', from.uid, '(', outPin, ')->', to.uid);
            }
            onExecutionUnlinked: {
                console.log("flow unlinked in func ", func.name, ': ', from.uid, '(', outPin, ')');
            }
        }

        Connections {
            target: Controller.Function
            onEntryPointSet: {
                console.log("entry point set for ", func, "(", func.id, ") => ", func.name, " at instruction ", entry.uid);
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
            Editor.createNode(canvas.nodeModel, choice, canvas.mousePosition.x, canvas.mousePosition.y);
    }

    SearchableMenu {
        id: _menu2
        itemHeight: 30
        itemWidth: 200
        matchViewWidth: 300
        model: Editor.contextMenuModel
        triggeredAction: onMenuNodeChoosen
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
