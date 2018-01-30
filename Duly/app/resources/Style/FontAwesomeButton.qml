import QtQuick 2.0
import QtQuick.Controls 2.2

MButton {
    id: control
    property alias label: _label
    property alias color: _label.color
    contentItem: FontAwesomeText {
        id: _label
        text: control.text
    }
}
