import QtQuick 2.9
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0

import Utils 1.0

import "../Style"
import "../../"

Item {
    id: _item

    Component {
        id: _delegate
        Rectangle {
            id: _column
            color: DulySettings.style.background.lightColor
            border.color: DulySettings.style.border.color
            border.width: DulySettings.style.border.width
            height: _item.height
            width: appWindow.width / 4
            EditableText {
                id: _title
                text:  model.name
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.left: parent.left
                anchors.right: parent.right
                placeholderText: "Section Title ..."
            }
            FontAwesomeButton {
                id: _commentbutton
                text: "\uf27a"
                label.font.pointSize: 14
                anchors.right: _title.right
                anchors.rightMargin: 5
                anchors.top: _title.top
                anchors.topMargin: -5
                color: hovered ? "#E6EE9C" : DulySettings.style.text.color
                background: Item {
                }
                onPressed: {
                    if (!_popup.opened)
                        _popup.open()
                }
            }
            Popup {
                id: _popup
                y: _commentbutton.y + _commentbutton.height - 6
                x: 10
                width: _column.width - 35
                padding: 20
                background: Rectangle {
                    border.color: DulySettings.style.border.color
                    color: DulySettings.style.menu.background.color
                }
                TextArea {
                    id: _comment
                    text: qsTr(model.comment)
                    anchors.fill: parent
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


            Item {
                id: _header
                anchors.top: _title.bottom
                anchors.topMargin: 16
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 25
                anchors.rightMargin: 30
                height: 30
                MLabel {
                    id: _selectInfo
                    property int selectCount: 0
                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    text: (selectCount > 1) ? selectCount + qsTr(" items selected") : selectCount + qsTr(" item selected")
                }
                FontAwesomeButton {
                    id: _deletebutton
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    width: 30
                    height: 30
                    label.font.pointSize: 12
                    text: "\uf2ed"
                    color: _deletebutton.hovered ? _selectInfo.selectCount != 0 ? DulySettings.style.text.color : "99000000" : "99000000"
                    background: Rectangle {
                        color: _deletebutton.hovered ? _selectInfo.selectCount != 0 ? "#99B71C1C" :  "transparent" : "transparent"
                    }
                }
            }

            ScrollView {
                anchors.top: _header.bottom
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: 5
                anchors.leftMargin: 5
                anchors.topMargin: 10
                anchors.bottomMargin: 10
                clip: true
                ListView {
                    property alias selectInfo: _selectInfo
                    anchors.fill: parent
                    model: item
                    delegate: _delegate1
                    spacing: 20
                    clip: true
                }
            }
        }
    }

    Component {
        id: _delegate1

        Rectangle {
            id: _itemview
            implicitHeight: 40
            anchors.left: parent.left
            anchors.leftMargin: 15
            anchors.right: parent.right
            anchors.rightMargin: 25
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
            }
            Item {
                anchors.left: _selectButton.right
                anchors.leftMargin: 5
                anchors.right: _openbutton.left
                anchors.rightMargin: 5
                anchors.top: _itemview.top
                anchors.bottom: _itemview.bottom
                EditableText {
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
    }

    ScrollView {
        anchors.fill: parent
        ListView {
            anchors.fill: parent
            spacing: -1
            orientation: Qt.Horizontal
            layoutDirection: Qt.LeftToRight
            model: Manager.declarationModel
            delegate: _delegate
        }
    }
}
