import QtQuick 2.9
import QtQuick.Controls 2.2
import CustomGeometry 1.0
import CustomViews 1.0
import Utils 1.0

import "../Nodes"
import "../Nodes/Operator"
import "../Nodes/Operator/BinaryOperator"
import "../Nodes/Operator/BinaryOperator/Logical"
import "../Nodes/Operator/UnaryOperator"

DropArea {
    id: dragTarget
    property int margin: 30
    property alias dropProxy: dragTarget
    DulyCanvas {
        id: canvas
        anchors.fill: parent
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
               model: SubstractModel {}
            }
            onScaleChanged: {
                zoomText.text = Math.round(content_item.scale * 100) + "%"
            }
        }
        content: content_item

//        Rectangle {
//            x:0
//            y:0
//            width: 100
//            height: 100
//        }

//        Node {
//           x: 0
//           y: 0
//           model: SubstractModel {}
//        }


//       Node {
//          x: 100
//          y: 100
//          model: AddNodeModel {}
//       }

        Label {
            id: zoomText
            text: (content_item.scale * 100) + "%"
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.top: parent.top
            anchors.topMargin: 20
        }


        //    ContextContainer {
        //        id: contextContainer
        //        anchors.topMargin: 20
        //        anchors.top: parent.top
        //        anchors.left: parent.left
        //        anchors.right: parent.right
        //    }

        //    ClassContainer {
        //        id: classContainer
        //        anchors.topMargin: 20
        //        anchors.top: contextContainer.bottom
        //        anchors.left: parent.left
        //        anchors.right: parent.right
        //    }

        //    VariableContainer {
        //        id: variableContainer
        //        anchors.topMargin: 20
        //        anchors.top: classContainer.bottom
        //        anchors.left: parent.left
        //        anchors.right: parent.right
        //    }

        //    FunctionContainer {
        //        id: methodContainer
        //        anchors.topMargin: 20
        //        anchors.top: variableContainer.bottom
        //        anchors.left: parent.left
        //        anchors.right: parent.right
        //    }
    }
}
