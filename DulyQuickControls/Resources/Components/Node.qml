import QtQuick 2.4
import QtQuick.Controls 2.2
import CustomGeometry 1.0

NodeForm {
    property NodeModel model
//    Drag.active: dragArea.drag.active
//    Drag.hotSpot.x: 10
//    Drag.hotSpot.y: 10

//    MouseArea {
//        id: dragArea
//        anchors.fill: parent
//        drag.target: parent
//    }
    id: nodeForm
    inputs: model.inputs
    outputs: model.outputs
    name: model.name
    description: model.description

    Flow {
        id: _flowIn
        radius: 6
        borderWidth: 3
        antialiasing: true
        x: radius
        y: headerRef.height / 2 - radius - radius / 3
        visible: model.flowIn
    }

    Flow {
        id: _flowOut
        radius: _flowIn.radius
        borderWidth: _flowIn.borderWidth
        antialiasing: _flowIn.antialiasing
        x: parent.width - radius * 4
        y: _flowIn.y
        visible: model.flowOut
    }

    flowInItem: _flowIn
    flowOutItem: _flowOut

    inputDelegate: Component {
        Item {
            width: 10
            height: 10
            x: i.radius * 2
            Input {
                id: i
                radius: 5
                type: t
                borderColor: {
                    if (t == IOType.Int)
                        toolBar.menuEditRef.settingRef.nodeTabRef.intBorderColorRef.colorSetting
                    else if (t == IOType.String)
                        toolBar.menuEditRef.settingRef.nodeTabRef.stringBorderColorRef.colorSetting
                    else if (t == IOType.Bool)
                        toolBar.menuEditRef.settingRef.nodeTabRef.boolBorderColorRef.colorSetting
                }
                fillColor: {
                    if (t == IOType.Int)
                        toolBar.menuEditRef.settingRef.nodeTabRef.intColorRef.colorSetting
                    else if (t == IOType.String)
                        toolBar.menuEditRef.settingRef.nodeTabRef.stringColorRef.colorSetting
                    else if (t == IOType.Bool)
                        toolBar.menuEditRef.settingRef.nodeTabRef.boolColorRef
                }
                Label {
                    anchors.topMargin: - i.radius / 2
                    anchors.leftMargin: i.radius * 4
                    text: n
                    anchors.left: parent.left
                    anchors.top: parent.top
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
            }
        }

    }
    outputDelegate: Component {
        Item {
            width: o.width
            height: o.height
            x: parent.parent.parent.width - o.radius * 4
            Output {
                id: o
                radius: 5
                type: t
                borderColor: {
                    if (t == IOType.Int)
                        toolBar.menuEditRef.settingRef.nodeTabRef.intBorderColorRef.colorSetting
                    else if (t == IOType.String)
                        toolBar.menuEditRef.settingRef.nodeTabRef.stringBorderColorRef.colorSetting
                    else if (t == IOType.Bool)
                        toolBar.menuEditRef.settingRef.nodeTabRef.boolBorderColorRef.colorSetting
                }
                fillColor: {
                    if (t == IOType.Int)
                        toolBar.menuEditRef.settingRef.nodeTabRef.intColorRef.colorSetting
                    else if (t == IOType.String)
                        toolBar.menuEditRef.settingRef.nodeTabRef.stringColorRef.colorSetting
                    else if (t == IOType.Bool)
                        toolBar.menuEditRef.settingRef.nodeTabRef.boolColorRef.colorSetting
                }
                Label {
                    anchors.topMargin: - o.radius / 2
                    anchors.leftMargin: - o.radius - width
                    text: n
                    anchors.left: parent.left
                    anchors.top: parent.top
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
            }
        }
    }
}
