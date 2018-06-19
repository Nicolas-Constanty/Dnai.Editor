import QtQuick 2.0

import QtQuick 2.0
import QtQuick.Controls 2.2
import Dnai.Controls 1.0

import "../Components"

BaseProperty {
    id: _panel

    signal typeChanged(var newType)

    anchors.left: parent.left
    anchors.right: parent.right
    height: header.height + _property.height + _panel.content.anchors.topMargin * 2

    Item {
        id: _property
        height: 35
        anchors.left: parent.left
        anchors.right: parent.right

        Label {
            id: _label
            text: qsTr("Value selected :")
            anchors.left: parent.left
            height: parent.height
            verticalAlignment: Text.AlignVCenter
            color: "#ffffff"
        }

        VarTypeComboBox {
            id: _type

            typeGuid: model ? model.guiProperties.varType : 0

            height: parent.height

            anchors.right: parent.right
            anchors.left: _label.right
            anchors.leftMargin: 5

            onTypeChanged: {
                _panel.typeChanged(newType);
            }
        }
    }

    onModelChanged: {
        if (model)
        {
            _type.typeGuid = model.guiProperties.varType;
        }
    }
}
