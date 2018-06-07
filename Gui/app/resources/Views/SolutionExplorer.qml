import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQml.Models 2.3
import DNAI 1.0
import DNAI.Models 1.0
import DNAI.Enums 1.0

import Dnai.FontAwesome 1.0

import "../Style"
import "../Components"
import "../Panels"

Rectangle {
    anchors.fill: parent
    color: "#16ffffff"
    property string title: "solution explorer"
    property real rowheight: 16
    property var last: null
    MLabel {
        id: _title
        height: 35
        padding: 15
        text: title
        color: "#CCFFFFFF"
        font.family: "segoeuisl"
        font.pointSize: 10
        font.capitalization: Font.AllUppercase
        anchors.left: parent.left
        anchors.top: parent.top
    }

    ListView {
        id: list
        model: Editor.solution
        orientation: Qt.Vertical
        anchors.top: _title.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: borderCreateId.top
        clip: true
//        focus: true

        highlight:  Item {
            y: list.currentItem.y;
            z: 5
            Rectangle {
                width: list.currentItem.width; height: list.currentItem.header.height
                color: "transparent"
                border.width: 1
                border.color: "#639DBD"
            }
        }
        delegate: ExpendablePanel {
            id: _expPanel
            title: name
            saved: item.saved
            panel.border.width: 0
            anchors.left: parent.left
            anchors.right: parent.right
            color: "transparent"
            control.onClicked: {
                list.currentIndex = index
                Editor.solution.selectProject(item)
                if (last !== control)
                    last.selected = false
                control.selected = true
                last = control
            }
            Timer {
                id: _timer
                interval: 200
                triggeredOnStart: false
                running: false
                repeat: false
                onTriggered: {
                    if (_expPanel.state == "Visible")
                    {
                        tr.verticalScrollBarPolicy = Qt.ScrollBarAsNeeded
                        tr.horizontalScrollBarPolicy = Qt.ScrollBarAsNeeded
                    }
                }
            }

            onStateChanged: {
                if (state == "Invisible")
                {
                    tr.verticalScrollBarPolicy = Qt.ScrollBarAlwaysOff
                    tr.horizontalScrollBarPolicy = Qt.ScrollBarAlwaysOff
                }
                else if (state == "Visible" && !_timer.running)
                {
                    _timer.start()
                }
            }

            header.height: 25
            titleobj.font.family: "segoeuib"
            titleobj.color: "#CCFFFFFF"
            titleobj.font.bold: true
            titleobj.font.pointSize: 8
            titleobj.font.capitalization: Font.AllUppercase

            Component.onCompleted: {
                console.log("Expendable panel item: ", item);
            }

            TreeView {
                id: tr
                property bool init: false
                signal rowInserted(var index, var start, var end)
                signal rowRemoved(var index, var start, var end)
                anchors.fill: parent
                anchors.bottomMargin: -5

                model: item
                selection: ItemSelectionModel {
                    model: item
                }

                frameVisible: false

                itemDelegate: Item {
                    Image {
                        id: _icon
                        source: "../Images/" + AppSettings.getEntityIcon(styleData.value.entityType)
                        height: 12
                        width: 12
                        anchors.verticalCenter: parent.verticalCenter
                        antialiasing: true
                    }
                    MLabel {
                        text: (styleData.value.name !== undefined) ? styleData.value.name : ""
                        horizontalAlignment: Text.AlignLeft
                        font.family: "segoeui"
                        font.pointSize: 8
                        color:  "#CCFFFFFF"
                        anchors.left: _icon.right
                        anchors.leftMargin: 5
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }

                rowDelegate: Item {
                    height: rowheight
                }

                TableViewColumn {
                    movable: false
                    resizable : false
                    role: "modelobj"
                }
                style: TreeViewStyle {
                    alternateBackgroundColor : "transparent"
                    backgroundColor : "transparent"
                    highlightedTextColor : AppSettings.theme["text"]["lightColor"]
                    textColor : AppSettings.theme["text"]["color"]
                }
                onClicked: {
                    var tab = Editor.selectedView()
                    var model = index.model.data(index, index.model.getRoleKey("modelobj"))
                    var res = tab.getViewFromModel(model)
                    if (res === -1)
                    {
                        var view;
                        if (model.entityType === 2)
                        {
                            view = tab.addView("resources/Components/NodeCanvas.qml",
                                        {}, index.model.data(index, index.model.getRoleKey("name")))
                        }
                        else
                        {
                            view = tab.addView("resources/Views/DeclarationView.qml",
                                    {
//                                        "model" : model.listColumn,
                                        "idx" : index,
                                        "proj" : index.model,
                                        "parentEntity": model
                                    },
                                    index.model.data(index, index.model.getRoleKey("name")))
                        }
                        tab.appendModel(model, view)
                    }
                    else
                    {
                        res.idx = index
                        res.proj = index.model
                        tab.selectIndex(res)
                    }
                }
                headerVisible: false
//                rootIndex: item.index(0, 0)
                onExpanded: {
                    index.model.data(index, index.model.getRoleKey("modelobj")).expanded = true
                    _expPanel.height += item.expandedRows(index) * rowheight
                    _expPanel.initialheight = _expPanel.height
                }

                onCollapsed: {
                    _expPanel.height -= item.expandedRows(index) * rowheight
                    _expPanel.initialheight = _expPanel.height
                    index.model.data(index, index.model.getRoleKey("modelobj")).expanded = false
                }

                Component.onCompleted: {
                    _expPanel.initialheight = rowheight + _expPanel.header.height + 5
                    item.rowsInserted.connect(tr.rowInserted)
                    item.rowsRemoved.connect(tr.rowRemoved)
                    if (item === Editor.solution.selectedProject())
                    {
                        _expPanel.control.selected = true
                        last = _expPanel.control
                    }
                }

                onRowInserted: {
                    if (index.model.data(index, index.model.getRoleKey("expended")))
                    {
                        _expPanel.height += (end + 1 - start) * rowheight
                        _expPanel.initialheight = _expPanel.height
                    }
                }

                onRowRemoved: {
                    if (index.model.data(index, index.model.getRoleKey("expended")))
                    {
                        _expPanel.height -= (end + 1 - start) * rowheight
                        _expPanel.initialheight = _expPanel.height
                    }
                }
            }
            transitions: Transition {
                NumberAnimation { properties: "y"; easing.type: Easing.InOutQuad }
            }
        }
    }

    Rectangle {
        id: borderCreateId
        anchors.bottom: createProjectItemId.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 1
        color: AppSettings.theme["shadowColor"]
    }

    Item {
        property int heightValue: containerId.childrenRect.height
        property bool editableProjectMode: false
        id: createProjectItemId
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: heightValue + 10

        function cancel() {
            createProjectItemId.editableProjectMode = false
            projectNameEditableId.text = ""
        }

        Rectangle {
            id: backgroundCreateProjectId
            anchors.fill: parent
            z: createProjectItemId.editableProjectMode ? parent.z : parent.z + 1
            color: cursorId.containsMouse ? AppSettings.theme["text"]["color"] : "transparent"
            opacity: cursorId.containsMouse ? 0.1 : 1.0

            MouseArea {
                id: cursorId
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                hoverEnabled: true
                enabled: !createProjectItemId.editableProjectMode

                onReleased: {
                    createProjectItemId.editableProjectMode = true
                }

            }
        }

        Item {
            id: containerId
            anchors.fill: parent
            anchors.margins: 10

            MLabel {
                font.pointSize: 13
                text: "Create Project"
                anchors.left: parent.left
                anchors.right: addId.left
                anchors.rightMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                visible: !createProjectItemId.editableProjectMode
            }

            EditableText {
                id: projectNameEditableId
                font.pointSize: 13
                text: ""
                placeholderText: ""
                visible: createProjectItemId.editableProjectMode
                focus: createProjectItemId.editableProjectMode
                anchors.left: parent.left
                anchors.right: addId.left
                anchors.rightMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: TextInput.AlignLeft
                enableBar: false
                Keys.onEscapePressed: {
                    createProjectItemId.editableProjectMode = false
                    projectNameEditableId.text = ""
                }
                Keys.onReturnPressed: {
                    createProjectItemId.editableProjectMode = false
                    Editor.addProject(projectNameEditableId.text, "")
                    projectNameEditableId.text = ""
//                    cursorId.
                }
            }

            TextAwesomeSolid {
                id: addId
                text: "\uf055"
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                font.pointSize: 20
                rotation: createProjectItemId.editableProjectMode ? 45 : 0
                color: mouseId.containsMouse == true ? AppSettings.theme["text"]["errorSelectedColor"] : createProjectItemId.editableProjectMode ? AppSettings.theme["text"]["errorColor"] : AppSettings.theme["background"]["bluecolor"]

                Behavior on rotation {
                    NumberAnimation { duration: 200 }
                }

                MouseArea {
                    id: mouseId
                    anchors.fill: parent
                    hoverEnabled: createProjectItemId.editableProjectMode
                    cursorShape: Qt.PointingHandCursor
                    enabled: createProjectItemId.editableProjectMode

                    onReleased: {
                        createProjectItemId.cancel()
                    }
                }

            }
        }
    }

/*    TextAwesomeSolid {
            id: arrowId
            text: "\uf055"
            anchors.verticalCenter: _title.verticalCenter
            anchors.right: parent.bottom
            anchors.rightMargin: 20
            font.pointSize: 15
            color: AppSettings.theme["background"]["bluecolor"]
        }*/

}



