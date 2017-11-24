import QtQuick 2.4
import QtQuick.Controls 1.4
import Utils 1.0

import "../JavaScript/CreateComponent.js" as Factory
import "../Forms"
import "../Layouts"

ChooseThemeForm {
    id: form

    panel.color: DulySettings.style.background

    Component.onCompleted:
    {
        themes.model = DulySettings.getThemes()
    }

    themes.onCurrentTextChanged: {
        DulySettings.loadTheme(themes.currentText)
    }

    labelRef.font.pixelSize: DulySettings.style.font.pixelSize
    labelRef.color: DulySettings.style.text.color
    labelRef.font.family: DulySettings.style.font.family

    validateButton.onClicked: {
        form.visible = false
        appWindow.width = 1280
        appWindow.height = 720
        Factory.createObjects("resources/Layouts/LayoutClassic.qml", {
                                  "width": appWindow.width,
                                  "height": appWindow.height,
                                  "color": "transparent"
                              }, appWindow)
        layout = Factory.getObject()
        layout.anchors.fill = layout.parent
//        form.destroy()
    }
}
