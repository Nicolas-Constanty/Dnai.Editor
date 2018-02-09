import QtQuick 2.9
import QtQuick.Controls 2.2
import CustomGeometry 1.0
import CustomViews 1.0
import Utils 1.0

import "../Style"
import "../Nodes"
import "../Nodes/Operator"
import "../Nodes/Operator/BinaryOperator"
import "../Nodes/Operator/BinaryOperator/Logical"
import "../Nodes/Operator/UnaryOperator"

DulyCanvas {
    id: canvas
    backgroundColor: DulySettings.style.canvas.background
    gridStep: DulySettings.style.canvas.grid.step
    gridColor: DulySettings.style.canvas.grid.color
    accentGridStep: DulySettings.style.canvas.grid.accentStep
    accentGridColor: DulySettings.style.canvas.grid.accentColor
    states: [
        State {
            when: dragTarget.containsDrag
            PropertyChanges {
                target: canvas
                backgroundColor: DulySettings.style.canvas.grid.selectColor
            }
        }
    ]
    Item {
        id: content_item
        x: canvas.width/2
        y: canvas.height/2
        Node {
           x: 0
           y: 0
           model: SubstractModel {}
        }

        Node {
           x: 100
           y: 100
           model: AddNodeModel {}
        }
        onScaleChanged: {
            zoomText.text = Math.round(content_item.scale * 100) + "%"
        }
    }
    content: content_item

    MLabel {
        id: zoomText
        text: (content_item.scale * 100) + "%"
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 20
    }
}
