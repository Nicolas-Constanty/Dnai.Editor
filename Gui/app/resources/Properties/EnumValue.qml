import QtQuick 2.0
import QtQuick.Controls 2.2
import Dnai.Controls 1.0
import Dnai.FontAwesome 1.0

Item {
    property ButtonAwesomeSolid moveUpButton: _moveUpButton
    property ButtonAwesomeSolid moveDownButton: _moveDownButton
    property ButtonAwesomeSolid deleButton: _deleteButton
    Row {
        id: _row
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        spacing: 2
        EditableText {
            text: model.value
            width: _values.width - _moveUpButton.width - _moveDownButton.width - _deleteButton.width - _row.spacing * 3
            height: _panel.contentHeight
            horizontalAlignment: TextInput.AlignLeft
        }
        ButtonAwesomeSolid {
            id: _moveUpButton
            height: _panel.contentHeight
            width: _panel.contentHeight
            label.text: "\uf0d7"
            label.font.pointSize: 14
            rotation: 180
        }
        ButtonAwesomeSolid {
            id: _moveDownButton
            height: _panel.contentHeight
            width: _panel.contentHeight
            label.text: "\uf0d7"
            label.font.pointSize: 14
        }
        ButtonAwesomeSolid {
            id: _deleteButton
            height: _panel.contentHeight
            width: _panel.contentHeight
            label.text: "\uf2ed"
            label.font.pointSize: 14
        }
    }
}
