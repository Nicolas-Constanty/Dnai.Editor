import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4

import "../Style"

Item {
    width: 400
    height: 100
    property alias panel: rectangle
    property alias labelRef: label
    property alias themes: comboBox
    property alias validateButton: validate

    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: 400
        height: 150

        MLabel {
            id: label
            x: 29
            y: 44
            text: qsTr("Please select a theme :")
        }

        ComboBox {
            id: comboBox
            x: 231
            y: 31
        }

        Button {
            id: validate
            x: 168
            y: 94
            text: qsTr("Ok")
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
