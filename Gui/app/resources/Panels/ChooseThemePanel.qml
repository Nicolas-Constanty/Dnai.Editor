import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Window 2.3
import DNAI 1.0

import "../JavaScript/CreateComponent.js" as Factory
import "../Forms"
import "../Layouts"
import DNAI 1.0

ChooseThemeForm {
    id: form
    width: 400
    height: 200
    property var wind: null

    panel.color: AppSettings.theme["background"]["color"]

    Component.onCompleted:
    {
        themes.model = AppSettings.getThemes()
    }

    themes.onCurrentTextChanged: {
        AppSettings.loadTheme(themes.currentText)
    }

    validateButton.onClicked: {
        form.visible = false
        wind.close()
        main.loadMain()
    }
}
