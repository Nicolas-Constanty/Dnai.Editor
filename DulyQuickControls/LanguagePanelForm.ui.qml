import QtQuick 2.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Item {

    property alias colRef: column
    property alias rectRef: rectangle
    property string languageDropDown: "Language"

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
                name: languageDropDown
                listModel: LanguageModel {
                }
                height: 40
            }
        }
    }
}
