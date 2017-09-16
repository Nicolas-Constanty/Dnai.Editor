import QtQuick 2.9
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.0
import "../Models"
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

            DropDown {
                name: "Theme"
                listModel: ThemeModel {
                }
                height: 40
            }

            ColorPicker {
                name: "Background Color"
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                height: 40
            }

            ColorPicker {
                name: "Fine Grid Color"
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                height: 40
            }

            ColorPicker {
                name: "Coarse Grid Color"
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                height: 40
            }
        }
    }
}
