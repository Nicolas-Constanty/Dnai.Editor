import QtQuick 2.0
import QtQuick.Controls 2.2

import Dnai.Controls 1.0
import Dnai.FontAwesome 1.0

Item {
    id: _parameterValue

    /**
     * Action buttons
     */
    property var moveUp: null
    property var moveDown: null
    property var deleteParameter: null
    property var parameterTypeChanged: null
    property var parameterNameChanged: null


    property real contentHeight: 24
    property var updateValue: null
    property var listmodel: null
    property var prop: null
    property alias name: _name.text
    property alias type: _type.currentIndex

    property bool init: false

    Row {
        id: _row
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        spacing: 2
        EditableText {
            id: _name
            width: _parameterValue.width - _moveUpButton.width - _moveDownButton.width - _deleteButton.width - _type.width - _row.spacing * 4
            height: _parameterValue.contentHeight
            horizontalAlignment: TextInput.AlignLeft
            onAccepted: {
                if (parameterNameChanged !== null) parameterNameChanged(_name.text)
            }
        }
        ComboBox {
            id: _type
            model: listmodel
            height: _parameterValue.contentHeight
            width: _parameterValue.contentHeight * 2
            onCurrentIndexChanged: {
                if (parameterNameChanged !== null) parameterTypeChanged(_type.currentIndex)
            }
        }
        ButtonAwesomeSolid {
            id: _moveUpButton
            height: _parameterValue.contentHeight
            width: _parameterValue.contentHeight
            label.text: "\uf0d7"
            label.font.pointSize: 14
            rotation: 180
            onClicked: {
//                console.log("on clicked move up");
                if (onMoveUp !== null) onMoveUp();
            }
        }
        ButtonAwesomeSolid {
            id: _moveDownButton
            height: _parameterValue.contentHeight
            width: _parameterValue.contentHeight
            label.text: "\uf0d7"
            label.font.pointSize: 14
            onClicked: {
                if (onMoveDown !== null) onMoveDown();
            }
        }
        ButtonAwesomeSolid {
            id: _deleteButton
            height: _parameterValue.contentHeight
            width: _parameterValue.contentHeight
            label.text: "\uf2ed"
            label.font.pointSize: 14
            onClicked: {
                if (onDelete !== null) onDelete();
            }
        }
    }
}
