import QtQuick 2.0
import QtQml.Models 2.3

import "../Nodes"
import "../Nodes/Operator/BinaryOperator"
import "../Style"

Item {

    Component {
        id: _listDelegate
        GridView {
            cellWidth: 60
            cellHeight: 60
            Component.onCompleted: {
                console.log(model)
                console.log(model.list)
            }

            model: DelegateModel {
                model: list
                delegate: Item {
                    id: _item
                    height: 60
                    width: 60
                    MouseArea {
                        id: _mouseArea
                        drag.target: tile
                        height: 50
                        width: 50
                        onReleased: {
                            var isDroppable = tile.Drag.target !== null
                            var obj = Factory.getObject()
                            if (obj != undefined && isDroppable)
                            {
                                obj.x = mouse.x
                                        + obj.x
                                        + obj.parent.x
                                        + obj.parent.parent.x
                                        + obj.parent.parent.parent.x
                                        + obj.parent.parent.parent.parent.x
                                        - tile.Drag.target.x
                                        - obj.width / 2
                                obj.y = mouse.y
                                        + obj.y
                                        + obj.parent.y
                                        + obj.parent.parent.y
                                        + obj.parent.parent.parent.y
                                        + obj.parent.parent.parent.parent.y
                                        - tile.Drag.target.y
                                        - obj.height / 2
                                obj.parent = tile.Drag.target
                            }
                        }
                        Rectangle {
                            id: tile
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter

                            height: parent.height
                            width: parent.width
                            color: model.color
                            radius: model.radius
                            border.color: model.borderColor
                            border.width: model.borderWidth

                            Drag.active: mouseArea.drag.active
                            Drag.hotSpot.x: height / 2
                            Drag.hotSpot.y: width / 2
                            MLabel {
                                id: label
                                text: model.name
                                anchors.centerIn: parent
                            }
                            states: State {
                                when: mouseArea.drag.active
                                ParentChange { target: tile; parent: item }
                                AnchorChanges { target: tile; anchors.verticalCenter: undefined; anchors.horizontalCenter: undefined }
                            }
                        }
                        onPressed: {
                            var obj = Factory.createObjects("resources/Components/Node.qml" ,
                                                  {
                                                      "width": 50,
                                                      "height": 50,
                                                      "model": model.item,
                                                  },
                                                  parent.parent)
                            obj.x = item.x
                            obj.y = item.y
                        }
                    }
                }
            }
        }
    }
    ListView {
        delegate: _listDelegate
    }
}
