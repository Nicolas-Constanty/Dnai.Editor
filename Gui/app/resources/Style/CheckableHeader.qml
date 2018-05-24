import QtQuick 2.0
import QtQuick.Controls 2.2

Button {
    id: _control
    checkable: true
    background: Rectangle {
        color: "#16ffffff"
        border.color: "#673AB7"
        border.width:  _control.checked ? 1 : 0
        anchors.fill: parent
    }
}
