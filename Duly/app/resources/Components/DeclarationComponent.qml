import QtQuick 2.9
import QtQuick.Controls 2.2
import CustomGeometry 1.0
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

        Rectangle {
            x: parent.width / 2
            y: parent.height / 2
            width: 5
            height: 5
        }

        Label {
            id: zoomText
            text: (canvas.scaleFactor * 100) + "%"
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.top: parent.top
            anchors.topMargin: 20
        }
        onScaleFactorChanged: {
            zoomText.text = Math.round(canvas.scaleFactor * 100) + "%"
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

