import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQml.Models 2.3
import DNAI 1.0
import DNAI.Models 1.0
import DNAI.Enums 1.0

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
        anchors.bottom: parent.bottom
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
                        source: styleData.value.entityType === 0 ? "../Images/context.png" : styleData.value.entityType === 1 ? "../Images/variable.png" : styleData.value.entityType === 2 ? "../Images/function.png" : "../Images/class.png"
                        height: 12
                        width: 12
                        anchors.verticalCenter: parent.verticalCenter
                        antialiasing: true
                    }
                    MLabel {
                        text: styleData.value.name
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
                    highlightedTextColor : AppSettings.style.text.lightColor
                    textColor : AppSettings.style.text.color
                }
                onClicked: {
                    var tab = Editor.selectedView()
                    var model = index.model.data(index, index.model.getRoleKey("modelobj")).listColumn()
                    var res = tab.getViewFromModel(model)
                    if (res === undefined || res === null)
                    {
                        var view = tab.addView("resources/Views/DeclarationView.qml",
                                    {
                                        "model" : model,
                                        "idx" : index,
                                        "proj" : index.model
                                    },
                                    index.model.data(index, index.model.getRoleKey("name")))
                        tab.appendModel(model, view)
                    }
                    else
                    {
                        tab.selectIndex(res)
                    }
                }
                headerVisible: false
                rootIndex: item.index(0, 0)
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
                    _expPanel.initialheight = item.childCount * rowheight + _expPanel.header.height + 5
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
}



