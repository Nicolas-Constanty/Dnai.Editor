import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import Qt.labs.settings 1.0
import Dnai.Settings 1.0

import "../Forms"

import DNAI 1.0

ThemePanelForm {
    property bool init: false
    themes.items.onCurrentTextChanged: {
        if (init && themes.items.currentText)
            AppSettings.currentTheme = AppSettings.themeNames[themes.items.currentText]
    }

    Component.onCompleted:
    {
        themes.items.model = AppSettings.themeNames
        for (var i = 0; i < themes.items.model.length; i++)
        {
            if (themes.items.model[i] === AppSettings.currentTheme)
            {
                themes.items.currentIndex = i
                break
            }
        }
        init = true
    }
}
