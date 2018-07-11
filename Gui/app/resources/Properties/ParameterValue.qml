import QtQuick 2.0
import QtQuick.Controls 2.2

import DNAI 1.0
import Dnai.Controls 1.0
import Dnai.FontAwesome 1.0
import Dnai.Theme 1.0

import "../Components"

Item {
    id: _parameterValue

    /**
     * Action buttons
     */
    signal moveUp()
    signal moveDown()
    signal deleteValue()
    signal typeChanged(var type)
    signal nameChanged(string name)

    property real contentHeight: 24
    property var updateValue: null
    property var prop: null
    property alias paramName: _name.text
    property alias varType: _type.typeGuid
    property var paramModel: null

    property bool init: false

    Row {
        id: _row
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        width: parent.width

        spacing: 2
        TextField {
            id: _name
            width: parent.width - _deleteButton.width - _row.spacing * 2 - _type.width
            height: 26
            font.pointSize: 8
            onAccepted: {
                _parameterValue.nameChanged(_name.text)
            }
        }
        VarTypeComboBox {
            id: _type

            anchors.verticalCenter: parent.verticalCenter

            onTypeChanged: {
                _parameterValue.typeChanged(newType)
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
        Button {
            id: _deleteButton
            height: _parameterValue.contentHeight
            awesomeIcon.text: "\uf2ed"
            awesomeIcon.size: 8
            topPadding: 0
            bottomPadding: 0
            anchors.verticalCenter: parent.verticalCenter

            onClicked: {
                _parameterValue.deleteValue();
            }
        }
    }
}
