import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQml.Models 2.3
import Utils 1.0

import "../JavaScript/CreateComponent.js" as Factory

DelegateModel {
    id: visualModel
    property ContextModel contextModel: ContextModel {}
    property ClassModel classModel: ClassModel {}
    property FunctionModel functionModel: FunctionModel {}
    property VariableModel variableModel: VariableModel {}

    model: ListModel {
            id : listmodel
            Component.onCompleted: {
                append({
                           type: contextModel.type,
                           name: contextModel.name,
                           description: contextModel.description,
                           xPos: contextModel.xPos,
                           yPos: contextModel.yPos,
                           radius: contextModel.radius,
                           color: contextModel.color,
                           borderColor: contextModel.borderColor,
                           borderWidth: contextModel.borderWidth
                       });
                append({
                           type: classModel.type,
                           name: classModel.name,
                           description: classModel.description,
                           xPos: classModel.xPos,
                           yPos: classModel.yPos,
                           radius: classModel.radius,
                           color: classModel.color,
                           borderColor: classModel.borderColor,
                           borderWidth: classModel.borderWidth
                       })
                append({
                           type: functionModel.type,
                           name: functionModel.name,
                           description: functionModel.description,
                           xPos: functionModel.xPos,
                           yPos: functionModel.yPos,
                           radius: functionModel.radius,
                           color: functionModel.color,
                           borderColor: functionModel.borderColor,
                           borderWidth: functionModel.borderWidth
                       })
                append({
                           type: variableModel.type,
                           name: variableModel.name,
                           description: variableModel.description,
                           xPos: variableModel.xPos,
                           yPos: variableModel.yPos,
                           radius: variableModel.radius,
                           color: variableModel.color,
                           borderColor: variableModel.borderColor,
                           borderWidth: variableModel.borderWidth
                       })
            }
    }

    delegate: Item {
        id: item
        height: 60
        width: 60
        MouseArea {
            id: mouseArea

            drag.target: tile

            onReleased: {
                var isDroppable = tile.Drag.target !== null
//                console.info(listmodel.count)
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

            height: 50
            width: 50
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
                Label {
                    id: label
                    text: model.name
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.centerIn: parent

                }
                states: State {
                    when: mouseArea.drag.active
                    ParentChange { target: tile; parent: item }
                    AnchorChanges { target: tile; anchors.verticalCenter: undefined; anchors.horizontalCenter: undefined }
                }
            }
            onPressed: {
                if (model.type == DeclarationType.Context)
                {
                    var obj = Factory.createObjects("resources/Components/ContextView.qml" ,
                                          {
                                              "width": 50,
                                              "height": 50,
                                              "name": model.name,
                                              "description": model.description,
                                              "xPos": model.xPos,
                                              "yPos": model.yPos,
                                              "radius": model.radius,
                                              "color": model.color,
                                              "borderColor": model.borderColor,
                                              "borderWidth": model.borderWidth
                                          },
                                          parent.parent)
                    obj.x = item.x
                    obj.y = item.y
                }
                else if (model.type == DeclarationType.Class)
                {
                    var obj = Factory.createObjects("resources/Components/ClassView.qml",
                                          {
                                              "width": 50,
                                              "height": 50,
                                              "name": model.name,
                                              "description": model.description,
                                              "xPos": model.xPos,
                                              "yPos": model.yPos,
                                              "radius": model.radius,
                                              "color": model.color,
                                              "borderColor": model.borderColor,
                                              "borderWidth": model.borderWidth
                                          },
                                          parent.parent)
                    obj.x = item.x
                    obj.y = item.y
                }
            }
        }
    }
}
