import QtQuick 2.0
import QtQuick.Controls 2.2

import Dnai.Controls 1.0
import Dnai.FontAwesome 1.0
import Dnai.Theme 1.0

Item {
    id: _enumValue

    signal movedUp()
    signal movedDown()
    signal removed()
    signal valueUpdated(string oldValue, string newValue)

    property string value
    property real contentHeight: 24
    property var model: null
    property var prop: null


    function getIndex() {
        for(var i = 0; i < parent.children.length; i++) {
            if (parent.children[i] === _enumValue)
            {
                return i
            }
         }
        return -1
    }

    Row {
        id: _row
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        spacing: 2
        TextField {
            id: _value
            text: value
            width: _enumValue.width - _moveUpButton.width - _moveDownButton.width - _deleteButton.width - _row.spacing * 3
            height: _enumValue.contentHeight
            horizontalAlignment: TextInput.AlignLeft
            font.pointSize: 7
            onAccepted: {
                _enumValue.valueUpdated(_enumValue.value, _value.text);
                /*if (_enumValue.updateValue === null)
                    return
                _enumValue.updateValue(_enumValue.model, _enumValue.prop, getIndex(), _value.text)*/
            }
        }
        Button {
            id: _moveUpButton
            height: _enumValue.contentHeight
            width: _enumValue.contentHeight
            awesomeIcon.text: "\uf0d7"
            awesomeIcon.size: 7
            rotation: 180
            onClicked: {
                _enumValue.movedUp();
            }
        }
        Button {
            id: _moveDownButton
            height: _enumValue.contentHeight
            width: _enumValue.contentHeight
            awesomeIcon.text: "\uf0d7"
            awesomeIcon.size: 7
            onClicked: {
                _enumValue.movedDown();
            }
        }
        Button {
            id: _deleteButton
            height: _enumValue.contentHeight
            width: _enumValue.contentHeight
            awesomeIcon.text: "\uf2ed"
            awesomeIcon.size: 7
            onClicked: {
                _enumValue.removed();
            }
        }
    }
}
