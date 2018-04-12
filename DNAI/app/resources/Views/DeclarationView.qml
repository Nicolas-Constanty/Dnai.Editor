import QtQuick 2.9
import QtQml.Models 2.3
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0

import DNAI 1.0
import DNAI.Models 1.0
import DNAI.Enums 1.0

import "../Style"
import "../Components"

Item {
    id: _item
    property alias model: _contextColumns.model
    property Project proj: null
    property var idx: null
    Component {
        id: _delegate
        Rectangle {
            id: _column
            color: AppSettings.style.background.lightColor
            border.color: AppSettings.style.border.color
            border.width: AppSettings.style.border.width
            height: _item.height
            width: 300
            EditableText {
                id: _title
                text: modelData.name
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.left: parent.left
                anchors.right: _commentbutton.left
                placeholderText: "Section Title ..."
            }
            FontAwesomeButton {
                id: _commentbutton
                text: "\uf27a"
                label.font.pointSize: 14
                anchors.right: _column.right
                anchors.rightMargin: 5
                anchors.top: _title.top
                anchors.topMargin: -5
                color: hovered ? "#E6EE9C" : AppSettings.style.text.color
                background: Item {
                }
                onPressed: {
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
                    border.color: AppSettings.style.border.color
                    color: AppSettings.style.menu.background.color
                }
                TextArea {
                    id: _comment
                    text: qsTr(modelData.description)
                    anchors.fill: parent
                    color: AppSettings.style.text.color
                    wrapMode: TextEdit.WordWrap
                    selectByMouse: true
                    font.italic: true
                    placeholderText: "comment..."
                    background: Rectangle {
                        color: AppSettings.style.menu.background.darkColor
                        border.color: AppSettings.style.background.lightColor
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
                    color: _deletebutton.hovered ? _selectInfo.selectCount != 0 ? AppSettings.style.text.color : "99000000" : "99000000"
                    background: Rectangle {
                        color: _deletebutton.hovered ? _selectInfo.selectCount != 0 ? "#99B71C1C" :  "transparent" : "transparent"
                    }
                    onPressed: {
                        if (_selectInfo.selectCount != 0)
                        {
                            _sublist.selectedItems.sort(function compareNombres(a, b) {
                                return b.row() - a.row();
                              })
                            for (var i = 0; i < _sublist.selectedItems.length; i++) {
                                proj.removeEntity(idx, _sublist.selectedItems[i])
                            }
                            _sublist.selectedItems = []
                            _selectInfo.selectCount = 0

                        }
                    }
                }
            }

            ScrollView {
                id: _scrollview
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
                    id: _sublist
                    property var selectedItems: []
                    property alias selectInfo: _selectInfo
                    property alias visualModel: _delegateModel
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.leftMargin: 15
                    anchors.rightMargin: 25

                    model: DelegateModel {
                        id: _delegateModel
                        model: modelData
                        delegate: CommonModelView {
                            tparent: _sublist
                        }
                    }
                    spacing: 15
                    clip: true
                    add: Transition {
                        NumberAnimation { property: "opacity"; from: 0; to: 1.0; duration: 400 }
                        NumberAnimation { property: "scale"; from: 0; to: 1.0; duration: 400 }
                    }

                    displaced: Transition {
                        NumberAnimation { properties: "x,y"; duration: 400; easing.type: Easing.OutBounce }

                        // ensure opacity and scale values return to 1.0
                        NumberAnimation { property: "opacity"; to: 1.0 }
                        NumberAnimation { property: "scale"; to: 1.0 }
                    }
                    footer: Row {
                        topPadding: 15
                        layoutDirection: Qt.RightToLeft
                        width: _sublist.width
                        spacing: 5
                        AddButton {
                            id: _addContext
                            width: 45
                            visible: modelData.parentRef.entityType === 0
                            onPressed: {
                                proj.addContext(_sublist.visualModel.items.count, modelData.listIndex, idx)
                                _sublist.positionViewAtEnd()
                            }
                        }
                        AddButton {
                            id: _addClass
                            decoration.color: "#039BE5"
                            width: 45
                            onPressed: {
                                proj.addClass(_sublist.visualModel.items.count, modelData.listIndex, idx)
                                _sublist.positionViewAtEnd()
                            }
                        }
                        AddButton {
                            id: _addFunction
                            decoration.color: "#8E24AA"
                            width: 45
                            onPressed: {
                                proj.addFunction(_sublist.visualModel.items.count, modelData.listIndex, idx)
                                _sublist.positionViewAtEnd()
                            }
                        }
                        AddButton {
                            id: _addVariable
                            decoration.color: "#FB8C00"
                            width: 45
                            onPressed: {
                                proj.addVariable(_sublist.visualModel.items.count, modelData.listIndex, idx)
                                _sublist.positionViewAtEnd()
                            }
                        }
                    }
                }
            }
        }
    }

    ScrollView {
        anchors.fill: parent
        clip: true
        ListView {
            id: _contextColumns
            anchors.fill: parent
            spacing: -1
            orientation: Qt.Horizontal
            layoutDirection: Qt.LeftToRight
            delegate: _delegate
        }
        Rectangle {
            id: _listCreator
            x: 300 * _contextColumns.count + 25
            anchors.top: parent.top
            anchors.topMargin: 15
            width: 250
            height: 30
            color: "#80000000"
            radius: 3
            MText {
                anchors.fill: parent
                anchors.margins: 10
                text: qsTr("Add new column...")
                font.pointSize: AppSettings.style.font.pixelSize
                horizontalAlignment: Qt.AlignLeft
                color: AppSettings.style.text.disableColor
                font.italic: true
            }
            MouseArea {
                anchors.fill: parent
                onPressed: {
                    _popupList.open()
                }
            }
            Popup {
                id: _popupList
                width: _listCreator.width + 12
                height: _listCreator.height * 2 + 10
                x: -6
                y: -6
                onOpened: {
                    _textInput.forceActiveFocus()
                }
                background: Rectangle{
                    color: AppSettings.style.background.lightColor
                    radius: 3
                }
                enter: Transition {
                    NumberAnimation { property: "opacity"; from: 0.0; to: 1.0 }
                }
                exit: Transition {
                    NumberAnimation { property: "opacity"; from: 1.0; to: 0.0 }
                }
                Rectangle {
                    x: -6
                    y: -6
                    width: 250
                    height: 30
                    color: "#80000000"
                    border.color: AppSettings.style.background.color
                    radius: 3
                    TextInput {
                        id: _textInput
                        anchors.fill: parent
                        anchors.margins: 10
                        color: AppSettings.style.text.color
                        wrapMode: TextEdit.WordWrap
                        selectByMouse: true
                        font.italic: true
                        verticalAlignment: Qt.AlignVCenter
                        font.family: AppSettings.style.font.family
                        MText {
                            anchors.fill: parent
                            text: qsTr("Add new column...")
                            font.pointSize: AppSettings.style.font.pixelSize
                            horizontalAlignment: Qt.AlignLeft
                            color: AppSettings.style.text.disableColor
                            font.italic: true
                            visible: !parent.text
                        }
                        onAccepted: {
                            _popupList.close()
                            var t = _textInput.text
                            _textInput.clear()
//                            Manager.views.createDeclarationList(t)
                        }
                    }
                }
            }
        }
    }
}
