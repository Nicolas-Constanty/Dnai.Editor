import QtQuick 2.0
import QtQuick.Controls 2.2
import Dnai.Controls 1.0
import Dnai.FontAwesome 1.0
import Dnai.Theme 1.0

import DNAI 1.0

BaseProperty {
    id: _panel
    property var listmodel: null

    property real contentHeight: 24
    property real valueSpacing: 5
    property Button createButton: _createButton

    signal addValue()
    signal deleteValue(string name)
    signal typeChanged(string name, var type)
    signal renamed(string name, string newName)
    signal moveUp(int index)
    signal moveDown(int index)

    anchors.left: parent.left
    anchors.right: parent.right
    height: (_panel.listmodel.rowCount() * (_panel.contentHeight + _panel.valueSpacing)) + _panel.header.height + _createButton.height + _panel.content.anchors.topMargin * 2 + _panel.spacing * _panel.content.children.length
    ListView {
        id: _inputs
        anchors.left: parent.left
        anchors.right: parent.right
        height: (_panel.listmodel.rowCount() * (_panel.contentHeight + _panel.valueSpacing))
        model: _panel.listmodel
        spacing: _panel.valueSpacing

        delegate: ParameterValue {
            anchors.left: parent.left
            anchors.right: parent.right
            height: _panel.contentHeight
            paramName: model.name
            varType: model.varType
            paramModel: model

            onMoveDown: {
                _panel.moveDown(index)
            }
            onMoveUp: {
                _panel.moveUp(index)
            }
            onDeleteValue: {
                _panel.deleteValue(name)
                _inputs.height -= _panel.contentHeight + _panel.valueSpacing
                _panel.height -= _panel.contentHeight + _panel.valueSpacing
            }
            onNameChanged: {
                _panel.renamed(model.name, name)
            }
            onTypeChanged: {
                _panel.typeChanged(name, type)
            }
        }
    }

    Button {
        id: _createButton
        awesomeIcon.text: "\uf055"
        anchors.horizontalCenter: parent.horizontalCenter
        awesomeIcon.size: 30
        height: 40
        width: 40
        awesomeIcon.color: "#ffffff"
        background: Rectangle {
            color: "transparent"
        }
        onClicked: {
            if (_panel !== null)
            {
                _panel.addValue()
                _inputs.height += _panel.contentHeight + _panel.valueSpacing
                _panel.height += _panel.contentHeight + _panel.valueSpacing
            }
        }
    }
}
