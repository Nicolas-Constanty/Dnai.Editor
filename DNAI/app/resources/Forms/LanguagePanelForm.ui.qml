import QtQuick 2.9
import QtQuick.Controls 2.2

import "../Models"
import "../Components"
import "../Panels"

BasePanel {
    property string languageDropDown: "Language"

    DropDown {
        height: 40
        name: languageDropDown
        listModel: LanguageModel {
        }
    }
}
