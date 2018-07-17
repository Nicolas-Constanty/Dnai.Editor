import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Window 2.3
import DNAI 1.0
import Dnai.Settings 1.0

import "../JavaScript/CreateComponent.js" as Factory
import "../Forms"

ChooseThemeForm {
    id: form
    width: 400
    height: 200
    property var wind: null

    panel.color: AppSettings.theme["colors"]["background"]["base"]

    Component.onCompleted:
    {
        themes.model = AppSettings.themeNames
    }

    themes.onCurrentTextChanged: {
        AppSettings.currentTheme = themes.currentText
    }

    validateButton.onClicked: {
        form.visible = false
        main.show();
        AppSettings.themeLoaded = true;
    }
}
