import QtQuick 2.0

import DNAI 1.0
import Dnai.FontAwesome 1.0

import "../Style"

Rectangle {
    id: __this__

    color: AppSettings.theme["background"]["greencolor"]

    signal build()

    function builded()
    {
        _rotator.stop();
    }

    width: __build_label__.width + 20

    MLabel {
        id: __build_label__
        anchors.centerIn: parent
        visible: !_rotator.running

        text: "Build"
        color: "white"
        font.pointSize: 8
        font.bold: true
    }

    TextAwesomeSolid {
        id: __build_icon__
        anchors.centerIn: parent
        visible: _rotator.running

        text: "\uf2f1"
        font.pointSize: 8
        color: "white"

        RotationAnimation {
            id: _rotator
            target: __build_icon__
            from: 0
            to: 360
            duration: 2000
            running: false
            loops: Animation.Infinite
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "white"
        opacity: __build_area__.containsMouse ? 0.1 : 0
    }

    MouseArea {
        id: __build_area__

        anchors.fill: parent
        hoverEnabled: true
        enabled: !_rotator.running

        cursorShape: _rotator.running ? Qt.BusyCursor : Qt.PointingHandCursor

        onClicked: {
            _rotator.start();
            __this__.build();
        }
    }
}
