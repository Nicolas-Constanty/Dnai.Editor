import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Controls 1.0 as C
import QtQuick.Controls.Styles 1.0

import DNAI 1.0

import "../Style"
import "../Forms";
import "../Components"

Popup {
    background: Rectangle {
        border.color: "#444"
        color: "#252526"
    }
    Component.onCompleted: {
        console.log('WORKS ?')
    }
}
