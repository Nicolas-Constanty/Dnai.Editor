import QtQuick 2.9
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0

import DNAI 1.0
import DNAI.Models 1.0
import DNAI.Enums 1.0
import Dnai.Settings 1.0
import Dnai.FontAwesome 1.0
import Dnai.Theme 1.0

import "../Style"
import "../JavaScript/CreateComponent.js" as Factory

Rectangle {
    id: _itemview
    property alias isSelected: _selectButton.checked
    property Item tparent: null

    implicitHeight: 40
    width: parent.parent.width
    height: 40
    color: AppSettings.theme["colors"]["background"]["base"]
    MouseArea {
        anchors.fill: parent;
        onClicked: {
            Editor.propertyView().model = modelData
            Editor.solution.selectedEntity = _itemview
        }
    }

    state: "UnSelect"
    states: [
        State{
            name: "Select"
            PropertyChanges{ target: _selectButton; width: parent.width * 0.25 }
        },
        State{
            name:"UnSelect"
            PropertyChanges{ target: _selectButton; width: parent.width * 0.04 }
        },
        State{
            name:"Hover"
            PropertyChanges{ target: _selectButton; width: parent.width * 0.08 }
        }
    ]
    transitions: [
        Transition {
            from: "Select"
            to: "UnSelect"

            SequentialAnimation{
                NumberAnimation {
                    target: _selectButton
                    property: "width"
                    duration: 200
                    easing.type: Easing.InOutQuad
                }
            }
        },
        Transition {
            from: "UnSelect"
            to: "Select"
            SequentialAnimation{
                NumberAnimation {
                    target: _selectButton
                    property: "width"
                    duration: 200
                }
            }
        },
        Transition {
            from: "Hover"
            to: "Select"
            SequentialAnimation{
                NumberAnimation {
                    target: _selectButton
                    property: "width"
                    duration: 100
                }
            }
        },
        Transition {
            from: "UnSelect"
            to: "Hover"
            SequentialAnimation{
                NumberAnimation {
                    target: _selectButton
                    property: "width"
                    duration: 100
                }
            }
        },
        Transition {
            from: "Hover"
            to: "UnSelect"
            SequentialAnimation{
                NumberAnimation {
                    target: _selectButton
                    property: "width"
                    duration: 100
                }
            }
        }
    ]
    CheckBox {
        id: _selectButton
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.Left
        width: parent.width * 0.025
        implicitWidth: parent.width * 0.04
        indicator: Rectangle {
            anchors.fill: _selectButton
            color: AppSettings.theme["entities"][Number(modelData.entityType).toString()]["color"]

            TextAwesomeSolid { // Entity checked
                id: _entityCheck
                anchors.top: parent.top
                anchors.topMargin: 5
                anchors.bottom: _expandbutton.top
                anchors.bottomMargin: 5
                anchors.right: parent.right
                anchors.left: parent.left
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                text: "\uf00c"
                font.pointSize: 10
                visible: _selectButton.checked
                color: "#99000000"
            }
            LabelAwesomeSolid {
                id: _expandbutton
                state: "Collapse"
                states: [
                    State{
                        name: "Expand"
                        PropertyChanges{ target: _itemview; height: 40 + _itemComment.height + 5 }
                    },
                    State{
                        name:"Collapse"
                        PropertyChanges{ target: _itemview; height: 40 }
                    }
                ]
                transitions: [
                    Transition {
                        from: "Expand"
                        to: "Collapse"

                        SequentialAnimation{
                            NumberAnimation {
                                target: _itemview
                                property: "height"
                                duration: 200
                                easing.type: Easing.InOutQuad
                            }
                        }
                    },
                    Transition {
                        from: "Collapse"
                        to: "Expand"
                        SequentialAnimation{
                            NumberAnimation {
                                target: _itemview
                                property: "height"
                                duration: 200
                            }
                        }
                    }
                ]
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.left: parent.left
                horizontalAlignment: Label.AlignHCenter
                padding: 0
                text: state == "Collapse" ? "\uf0d7" : "\uf0d8"
                color: "#99000000"
                verticalAlignment: Qt.AlignBottom
                font.pointSize: 8
                background: Rectangle {
                    anchors.fill: _expandbutton
                    color: _expandbutton.hovered ? "#60ffffff" : "transparent"
                    Rectangle { // border top
                        height: 1
                        color: "#99000000"
                        anchors.top: parent.top
                        anchors.right: parent.right
                        anchors.left: parent.left
                    }
                }
                MouseArea {
                    id: _expender
                    anchors.fill: parent
                    onClicked: {
                        if (_expandbutton.state === "Collapse")
                            _expandbutton.state = "Expand"
                        else
                            _expandbutton.state = "Collapse"
                    }
                }
            }
        }

        onCheckStateChanged: {
            if (tparent.selectedItems.indexOf(modelData) === -1)
            {
                tparent.selectedItems.push(modelData)
            }
            else
                tparent.selectedItems.pop(modelData)
            if (_selectButton.checked)
            {
                _itemview.parent.parent.selectInfo.selectCount += 1
                _itemview.state = "Select"
            }
            else
            {
                _itemview.parent.parent.selectInfo.selectCount -= 1
                _itemview.state = "UnSelect"
            }
        }
        onHoveredChanged: {
            if (_selectButton.hovered && _itemview.state === "UnSelect")
                _itemview.state = "Hover"
            if (!_selectButton.hovered && _itemview.state === "Hover")
                _itemview.state = "UnSelect"
        }
    }
    ButtonAwesomeSolid {
        id: _openbutton
        visible: modelData.entityType === CoreEnums.FUNCTION
        anchors.right: _itemview.right
        anchors.top: _itemview.top
        anchors.bottom: _itemview.bottom
        width: 40
        text: "\uf35d"
        font.pointSize: 15
        color: _openbutton.hovered ? AppSettings.theme["text"]["color"] : "#80DEEA"
        background: Rectangle {
            id: _openbuttonBack
            color: _openbutton.hovered ? "#8080DEEA" : AppSettings.theme["colors"]["background"]["base"]
        }
        Rectangle {
            color: "transparent"
            border.color: "#4D000000"
            border.width: 1
            width: 1
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left
        }
        Glow {
            visible: _openbutton.hovered
            anchors.fill: _openbutton.label
            radius: 4
            samples: 17
            color: "#80DEEA"
            source: _openbutton.label
        }
        onPressed: {
            if (modelData.entityType === CoreEnums.FUNCTION)
            {
                var tab = Editor.selectedView()
                var model = modelData
                var res = tab.getViewFromModel(model)

                if (res === -1)
                {
                    var view = tab.addView("resources/Components/NodeCanvas.qml",
                                { "nodeModel": modelData, "entityModel": modelData.guiProperties}, modelData.name)
                    Editor.loadFunction(modelData)
                    tab.appendModel(modelData, view)
                }
                else
                {
                    tab.selectIndex(res)
                }
            }
        }
    }
    Item {
        anchors.left: _selectButton.right
        anchors.leftMargin: 5
        anchors.right: _openbutton.left
        anchors.rightMargin: 5
        anchors.top: _itemview.top
        anchors.bottom: _itemview.bottom
        Label {
            id: _itemName
            font.pointSize: 10
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            text: modelData.name
            horizontalAlignment: Qt.AlignLeft
            height: _itemview.implicitHeight
            clip: true
        }
        TextArea {
            id: _itemComment
            anchors.top: _itemName.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            visible: _expandbutton.state === "Expand"
            text: qsTr(modelData.description)
            color: AppSettings.theme["text"]["color"]
            wrapMode: TextEdit.WordWrap
            selectByMouse: true
            font.italic: true
            placeholderText: "comment..."
            background: Rectangle {
                color: AppSettings.theme["menu"]["background"]["darkColor"]
                border.color: AppSettings.theme["colors"]["background"]["light"]
            }
        }
    }
    layer.enabled: true
    layer.effect: DropShadow {
        transparentBorder: true
        horizontalOffset: 2
        verticalOffset: 2
        samples: 17
        color: "#80000000"
    }
    Rectangle {
        anchors.fill: parent
        border.width: Editor.solution.selectedEntity === _itemview ? 1 : 0
        border.color: AppSettings.theme["border"]["color"]
        color: Editor.solution.selectedEntity === _itemview ? "#1A63BB8C" : "transparent"
    }
}
