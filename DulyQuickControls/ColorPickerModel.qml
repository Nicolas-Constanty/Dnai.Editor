import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import Qt.labs.settings 1.0
import QtQuick.Controls.Material 2.2

ListModel {
//    ListElement
//    {
//        label: "Theme"
//        content: [
//            ListElement { dark: "Dark" },
//            ListElement { light: "Light" }
//        ]
//    }

    ListElement {
        label: "Background color"
        content: Material.Grey
    }
    ListElement {
        label: "Grid color"
        content: Material.Grey
    }
    ListElement {
        label: "Fine grid color"
        content: Material.Grey
    }
}
