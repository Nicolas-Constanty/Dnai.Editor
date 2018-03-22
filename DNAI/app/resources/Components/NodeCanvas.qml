import QtQuick 2.9
import QtQuick.Controls 2.3

import DNAI.Views 1.0
import DNAI 1.0
import DNAI.Models 1.0

import "../Style"
import "../Nodes"
import "../Nodes/Operator"
import "../Nodes/Operator/BinaryOperator"
import "../Nodes/Operator/BinaryOperator/Logical"
import "../Nodes/Operator/UnaryOperator"

CanvasNode {
    id: canvas
    clip: true
    anchors.fill: parent
    backgroundColor: AppSettings.style.canvas.background
    gridStep: AppSettings.style.canvas.grid.step
    gridColor: AppSettings.style.canvas.grid.color
    accentGridStep: AppSettings.style.canvas.grid.accentStep
    accentGridColor: AppSettings.style.canvas.grid.accentColor
    states: [
        State {
            when: dragTarget.containsDrag
            PropertyChanges {
                target: canvas
                backgroundColor: AppSettings.style.canvas.grid.selectColor
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
    }
    content: content_item

    onContextMenuChanged: {
        _menu.popup()
    }

    Menu {
        id: _menu

        Repeater {
            model: Manager.views.basicNodesModel
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
                                    Manager.createNode(item)
                                }
                            }
                        }
                    }
                }
                MenuSeparator {
                    id: _sepMenu
                }
                Component.onCompleted: {
                    _menu.addMenu(_subMenu)
                    _menu.addItem(_sepMenu)
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
