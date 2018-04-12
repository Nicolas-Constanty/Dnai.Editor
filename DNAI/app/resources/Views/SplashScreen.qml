import QtQuick 2.0
import QtQuick.Window 2.1
import DNAI 1.0

import "../Components"

Window {
    id: splash
    color: "transparent"
    title: "Splash Window"
    modality: Qt.ApplicationModal
    flags: Qt.SplashScreen
    property int timeoutInterval: 2000
    signal timeout
    x: (Screen.width - sprite.width) / 2
    y: (Screen.height - sprite.height) / 2
    width: sprite.width
    height: sprite.height
    visible: true

    AnimatedSprite {
        id: sprite
        width: 164
        height: 256
        source: "../Images/LoadingSprite.png"
        frameRate: 15
        interpolate: true
        frameCount: 120
        frameWidth: 164
        frameHeight: 256
    }
    Component.onCompleted: {
//        Editor.startApp()
    }
}
