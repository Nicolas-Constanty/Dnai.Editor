import QtQuick 2.0
import QtQuick.Controls 2.2
import Dnai.Controls 1.0
import Dnai.FontAwesome 1.0

BaseProperty {
    id: _panel
    property var listmodel: null
    property real contentHeight: 24
    property real valueSpacing: 5
    property ButtonAwesomeSolid createButton: _createButton

    anchors.left: parent.left
    anchors.right: parent.right
    height: _createButton.height + _values.height + _panel.content.anchors.topMargin * 2 + _panel.header.height - _panel.valueSpacing + _panel.spacing * 2

    ListModel {
        id: _testModel
        ListElement {
            name: "size"
            type: 2
        }
        ListElement {
            name: "name"
            type: 2
        }
    }
    Item {
        id: _values
        anchors.left: parent.left
        anchors.right: parent.right
        height: (_panel.contentHeight + _panel.valueSpacing) * _panel.model[prop].length

        ListView {
            anchors.fill: parent
            spacing: _panel.valueSpacing
            model: _testModel
            onModelChanged: {
                _panel.height = _panel.height = _createButton.height + (_panel.contentHeight + _panel.valueSpacing) * _panel.model[prop].length + _panel.content.anchors.topMargin * 2 + _panel.header.height - _panel.valueSpacing + _panel.spacing * 2
            }

            delegate: ParameterValue {
                name: model.name
                prop: _panel.prop
                height: _panel.contentHeight
                anchors.left: parent.left
                anchors.right: parent.right
                contentHeight: _panel.contentHeight

                function moveUp() {
                    if (_panel.model !== null)
                    {
//                        console.log("on move up")
                        _panel.model.moveUp(index)
                    }
                }
                moveUp: moveUp

                function moveDown() {
                    if (_panel.model !== null)
                    {
//                        console.log("on move down");
                        _panel.model.moveDown(index)
                    }
                }
                moveDown: moveDown

                function deleteVal() {
                    if (_panel.model !== null)
                    {
                        console.log("on delete");
                        _panel.model.deleteEntry(value)
                    }
                }
                deleteParameter: deleteVal

                function nameChanged(val) {
                    console.log(val)
                }
                parameterNameChanged: nameChanged

                function typeChanged(val) {
                    console.log(val)
                }
                parameterTypeChanged: typeChanged
            }
        }
    }
    ButtonAwesomeSolid {
        id: _createButton
        label.text: "\uf055"
        anchors.horizontalCenter: parent.horizontalCenter
        label.font.pointSize: 30
        height: 40
        width: 40
        color: "#ffffff"
        background: Rectangle {
            color: "transparent"
        }
        onClicked: {
            if (_panel.model !== null)
            {
                _panel.model.addEntry("");
            }
        }
    }
}
