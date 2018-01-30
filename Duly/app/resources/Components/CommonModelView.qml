import QtQuick 2.9
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0

import Utils 1.0
import "../Style"

Rectangle {
    id: _itemview
    property alias isSelected: _selectButton.checked
    implicitHeight: 40
    width: parent.parent.width
    height: 40
    color: DulySettings.style.background.color
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
                    duration: 200
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
            color: (model.item.type === 0) ? "#00897B" : (model.item.type === 1) ? "#039BE5" : (model.item.type === 2) ? "#8E24AA" : "#FB8C00"
            FontAwesomeText {
                anchors.fill: parent
                text: "\uf00c"
                font.pointSize: 15
                visible: _selectButton.checked
                color: "#99000000"
            }
            FontAwesomeButton {
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
                height: 8
                padding: 0
                text: state == "Collapse" ? "\uf0dd" : "\uf0d8"
                color: "#99000000"
                label.padding: 0
                label.verticalAlignment: Qt.AlignBottom
                label.font.pointSize: 10
                background: Rectangle {
                    color: _expandbutton.hovered ? "#60ffffff" : "transparent"
                }
                onClicked: {
                    if (state === "Collapse")
                        state = "Expand"
                    else
                        state = "Collapse"
                }
            }
            Rectangle {
                height: 1
                color: "#50000000"
                anchors.top: _expandbutton.top
                anchors.right: parent.right
                anchors.left: parent.left
            }
        }

        onCheckStateChanged: {
            model.item.select(_selectButton.checked)
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
    FontAwesomeButton {
        id: _openbutton
        visible: model.item.type < 3

        anchors.right: _itemview.right
        anchors.top: _itemview.top
        anchors.bottom: _itemview.bottom
        width: 40
        text: "\uf35d"
        font.pointSize: 15
        color: _openbutton.hovered ? DulySettings.style.text.color : "#80DEEA"
        background: Rectangle {
            color: _openbutton.hovered ? "#8080DEEA" : DulySettings.style.background.color
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
            appWindow.layout.leftPanel.treeview.changeCurrentFromModel(model.item)
        }
    }
    Item {
        anchors.left: _selectButton.right
        anchors.leftMargin: 5
        anchors.right: _openbutton.left
        anchors.rightMargin: 5
        anchors.top: _itemview.top
        anchors.bottom: _itemview.bottom
        MText {
            id: _itemName
            font.pointSize: 10
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            text: model.item.name
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
            text: qsTr(model.item.description)
            color: DulySettings.style.text.color
            wrapMode: TextEdit.WordWrap
            selectByMouse: true
            font.italic: true
            placeholderText: "comment..."
            background: Rectangle {
                color: DulySettings.style.menu.background.darkColor
                border.color: DulySettings.style.background.lightColor
            }
        }
    }
    layer.enabled: true
    layer.effect: DropShadow {
        transparentBorder: true
        horizontalOffset: 3
        verticalOffset: 3
        samples: 17
        color: "#80000000"
    }
}
