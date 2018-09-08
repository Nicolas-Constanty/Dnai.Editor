import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4

import Dnai.Theme 1.0

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

        Item {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: validate.top
            anchors.bottomMargin: 10
            anchors.margins: 20
            Label {
                id: label
                text: qsTr("Please select a theme :")
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
            }

            ComboBox {
                id: comboBox
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Button {
            id: validate
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10

            text: qsTr("Ok")
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
