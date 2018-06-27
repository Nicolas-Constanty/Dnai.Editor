import QtQuick 2.9
import QtQml.Models 2.3
import QtQuick.Controls 2.3
import QtGraphicalEffects 1.0

import DNAI 1.0
import DNAI.Models 1.0
import DNAI.Enums 1.0
import DNAI.Core 1.0

import Dnai.Settings 1.0
import Dnai.FontAwesome 1.0

import "../Style"
import "../Components"

Item {
    id: _item
//    property alias model: _contextColumns.model
    property Project proj: null
    property var idx: null
    property var parentEntity: null

    Component {
        id: _delegate
        Rectangle {
            id: _column
            color: AppSettings.theme["colors"]["background"]["light"]
            border.color: AppSettings.theme["border"]["color"]
            border.width: AppSettings.theme["border"]["width"]
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
                enableBar: false
            }
            ButtonAwesome {
                id: _commentbutton
                text: "\uf27a"
                label.font.pointSize: 14
                anchors.right: _column.right
                anchors.rightMargin: 5
                anchors.top: _title.top
                anchors.topMargin: -5
                color: hovered ? "#E6EE9C" : AppSettings.theme["text"]["color"]
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
                    border.color: AppSettings.theme["border"]["color"]
                    color: AppSettings.theme["menu"]["background"]["color"]
                }
                TextArea {
                    id: _comment
                    text: qsTr(modelData.description)
                    anchors.fill: parent
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
                ButtonAwesome {
                    id: _deletebutton
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    width: 30
                    height: 30
                    label.font.pointSize: 12
                    text: "\uf2ed"
                    color: _deletebutton.hovered ? _selectInfo.selectCount != 0 ? AppSettings.theme["text"]["color"] : "99000000" : "99000000"
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
                                Controller.declarator.remove(_sublist.selectedItems[i].containerId, _sublist.selectedItems[i].name)
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
                        id: _addRow

                        topPadding: 15
                        layoutDirection: Qt.RightToLeft
                        width: _sublist.width
                        spacing: 5

                        property int itemWidth: (_sublist.width - spacing * (children.length - 1)) / children.length

                        AddButton {
                            id: _addContext
                            width: _addRow.itemWidth
                            visible: (modelData.parentRef === null || modelData.parentRef.entityType === CoreEnums.CONTEXT)
                            toolTipsText: "Context"

                            onPressed: {
                                var name = proj.generateUniqueChildName(modelData.parentRef);

                                proj.addEntityColumnUid(modelData.parentRef.id, name, modelData.listIndex)
                                Controller.declarator.declare(modelData.parentRef.id, CoreEnums.CONTEXT, name)
                            }
                        }
                        AddButton {
                            id: _addClass
                            property int type: CoreEnums.OBJECT_TYPE
                            decoration.color: AppSettings.theme["entities"][Number(type).toString()]["color"]
                            width: _addRow.itemWidth
                            toolTipsText: "Class"

                            onPressed: {
                                var name = proj.generateUniqueChildName(modelData.parentRef);

                                proj.addEntityColumnUid(modelData.parentRef.id, name, modelData.listIndex)
                                Controller.declarator.declare(modelData.parentRef.id, type, name)
                            }
                        }
                        AddButton {
                            id: _addFunction
                            property int type: CoreEnums.FUNCTION
                            decoration.color: AppSettings.theme["entities"][Number(type).toString()]["color"]
                            width: _addRow.itemWidth
                            toolTipsText: "Function"

                            onPressed: {
                                var name = proj.generateUniqueChildName(modelData.parentRef);

                                proj.addEntityColumnUid(modelData.parentRef.id, name, modelData.listIndex)
                                Controller.declarator.declare(modelData.parentRef.id, type, name)
                            }
                        }
                        AddButton {
                            id: _addEnum
                            visible: (modelData.parentRef === null || modelData.parentRef.entityType === CoreEnums.CONTEXT || modelData.parentRef.entityType === CoreEnums.OBJECT_TYPE)
                            property int type: CoreEnums.ENUM_TYPE
                            decoration.color: AppSettings.theme["entities"][Number(type).toString()]["color"]
                            width: _addRow.itemWidth
                            toolTipsText: "Enum"

                            onPressed: {
                                var name = proj.generateUniqueChildName(modelData.parentRef);

                                proj.addEntityColumnUid(modelData.parentRef.id, name, modelData.listIndex)
                                Controller.declarator.declare(modelData.parentRef.id, type, name)
                            }
                        }
                        AddButton {
                            id: _addVariable
                            property int type: CoreEnums.VARIABLE
                            toolTipsText: "Variable"

                            decoration.color: AppSettings.theme["entities"][Number(type).toString()]["color"]
                            width: _addRow.itemWidth
                            onPressed: {
                                var name = proj.generateUniqueChildName(modelData.parentRef);

                                proj.addEntityColumnUid(modelData.parentRef.id, name, modelData.listIndex)
                                Controller.declarator.declare(modelData.parentRef.id, type, name)
                            }
                        }
                        AddButton {
                            id: _addList
                            property int type: CoreEnums.LIST_TYPE
                            toolTipsText: "List"

                            decoration.color: AppSettings.theme["entities"][Number(type).toString()]["color"]
                            width: _addRow.itemWidth
                            onPressed: {
                                var name = proj.generateUniqueChildName(modelData.parentRef);

                                proj.addEntityColumnUid(modelData.parentRef.id, name, modelData.listIndex)
                                Controller.declarator.declare(modelData.parentRef.id, type, name)
                            }
                        }
                    }

                    Connections {
                        target: proj
                        onEntityAdded: {
                            _sublist.positionViewAtEnd()
                        }
                        onEntityRemoved: {
                            _sublist.positionViewAtEnd()
                        }
                    }
                }
            }
        }
    }

    Component.onCompleted: {
        console.log(parent)
    }

    ScrollView {
        id: _scrollColumn
        anchors.fill: parent
        contentHeight: _contentView.height
        contentWidth: _contentView.width
        ScrollBar.horizontal.interactive: true

        Item {
            id: _contentView
            height: _item.height
            width: childrenRect.width + 25

            ListView {
                id: _contextColumns
                height: parent.height
                width: _item.parentEntity.listColumn.length * 300
                model: _item.parentEntity.listColumn
                spacing: -1
                orientation: Qt.Horizontal
                layoutDirection: Qt.LeftToRight
                delegate: _delegate
                interactive: false
            }
            Rectangle {
                id: _listCreator
                anchors.top: parent.top
                anchors.topMargin: 15
                anchors.left: _contextColumns.right
                anchors.leftMargin: 25
                width: 250
                height: 30
                color: "#80000000"
                radius: 3
                MText {
                    anchors.fill: parent
                    anchors.margins: 10
                    text: qsTr("Add new column...")
                    font.pointSize: AppSettings.theme["font"]["pixelSize"]
                    horizontalAlignment: Qt.AlignLeft
                    color: AppSettings.theme["text"]["disableColor"]
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
                        color: AppSettings.theme["colors"]["background"]["light"]
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
                        border.color: AppSettings.theme["colors"]["background"]["base"]
                        radius: 3
                        TextInput {
                            id: _textInput
                            anchors.fill: parent
                            anchors.margins: 10
                            color: AppSettings.theme["text"]["color"]
                            wrapMode: TextEdit.WordWrap
                            selectByMouse: true
                            font.italic: true
                            verticalAlignment: Qt.AlignVCenter
                            font.family: AppSettings.theme["font"]["family"]
                            MText {
                                anchors.fill: parent
                                text: qsTr("Add new column...")
                                font.pointSize: AppSettings.theme["font"]["pixelSize"]
                                horizontalAlignment: Qt.AlignLeft
                                color: AppSettings.theme["text"]["disableColor"]
                                font.italic: true
                                visible: !parent.text
                            }
                            onAccepted: {
                                var t = _textInput.text
                                _popupList.close()
                                _textInput.clear()
                                _item.parentEntity.addColumn(t);
                            }
                        }
                    }
                }
            }
        }

    }

}
