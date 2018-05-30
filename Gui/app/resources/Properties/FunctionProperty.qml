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

    property var addValue: null

    property var moveDown: null
    property var moveUp: null
    property var deleteValue: null
    property var nameChanged: null
    property var typeChanged: null


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
            name: model.name
            varType: model.varType
            paramModel: model

            moveDown: function () {
                _panel.moveDown(index)
            }
            moveUp: function () {
                _panel.moveUp(index)
            }
            deleteValue: function () {
                _panel.deleteValue(name)
                _inputs.height -= _panel.contentHeight + _panel.valueSpacing
                _panel.height -= _panel.contentHeight + _panel.valueSpacing
            }
            nameChanged: function (n) {
                _panel.nameChanged(index, model.name, n)
            }
            typeChanged: function (t) {
                console.log("model: ", paramModel.id);
                console.log("_inputs[index]: ", _inputs[index]);
                _panel.typeChanged(index, name, t)
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
            if (_panel !== null)
            {
                _panel.addValue()
                _inputs.height += _panel.contentHeight + _panel.valueSpacing
                _panel.height += _panel.contentHeight + _panel.valueSpacing
            }
        }
    }
}
