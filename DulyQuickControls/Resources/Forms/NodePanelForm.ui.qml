import QtQuick 2.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "../Components"

Item {

    property alias colRef: column
    property alias rectRef: rectangle

    ScrollView {
        id: rectangle
        anchors.rightMargin: 20
        anchors.leftMargin: 20
        anchors.bottomMargin: 20
        anchors.topMargin: 50
        anchors.fill: parent

        ColumnLayout {
            id: column
            spacing: 0
            ColorPicker {
                name: "FontColor"
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                height: 40
            }
            ColorPicker {
                name: "FontColorFaded"
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                height: 40
            }

            ColorPicker {
                name: "ShadowColor"
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                height: 40
            }

            ColorPicker {
                name: "ConnectionPointColor"
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                height: 40
            }

            ColorPicker {
                name: "FilledConnectionPointColor"
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                height: 40
            }
        }
    }
}
