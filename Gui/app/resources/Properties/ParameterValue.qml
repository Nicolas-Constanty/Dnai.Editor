import QtQuick 2.0
import QtQuick.Controls 2.2

import DNAI 1.0
import Dnai.Controls 1.0
import Dnai.FontAwesome 1.0

import "../Components"

Item {
    id: _parameterValue

    /**
     * Action buttons
     */
    property var moveUp: null
    property var moveDown: null
    property var deleteValue: null
    property var typeChanged: null
    property var nameChanged: null

    property real contentHeight: 24
    property var updateValue: null
    property var prop: null
    property alias name: _name.text
    property alias varType: _type.typeGuid
    property var paramModel: null

    property bool init: false

    Row {
        id: _row
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        width: parent.width

        spacing: 2
        EditableText {
            id: _name
            width: (parent.width - _deleteButton.width) * 0.5
            height: _parameterValue.contentHeight
            horizontalAlignment: TextInput.AlignLeft
            onAccepted: {
                if (nameChanged !== null) nameChanged(_name.text)
            }
        }
        VarTypeComboBox {
            id: _type

            height: _parameterValue.contentHeight
            width: (parent.width - _deleteButton.width) * 0.5

            onTypeChanged: {
                if (_parameterValue.typeChanged !== null)
                    _parameterValue.typeChanged(_type.currentIndex)
            }
        }
        /*ButtonAwesomeSolid {
            id: _moveUpButton
            height: _parameterValue.contentHeight
            width: _parameterValue.contentHeight
            label.text: "\uf0d7"
            label.font.pointSize: 14
            rotation: 180
            onClicked: {
//                console.log("on clicked move up");
                if (moveUp !== null) moveUp();
            }
        }
        ButtonAwesomeSolid {
            id: _moveDownButton
            height: _parameterValue.contentHeight
            width: _parameterValue.contentHeight
            label.text: "\uf0d7"
            label.font.pointSize: 14
            onClicked: {
                if (moveDown !== null) moveDown();
            }
        }*/
        ButtonAwesomeSolid {
            id: _deleteButton
            height: _parameterValue.contentHeight
            width: 40
            label.text: "\uf2ed"
            label.font.pointSize: 8
            onClicked: {
                if (deleteValue !== null) deleteValue();
            }
        }
    }
}
