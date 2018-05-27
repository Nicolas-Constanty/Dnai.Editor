import QtQuick 2.0
import QtQuick.Controls 2.2

import Dnai.Controls 1.0

PanelView {
    id: _panel
    property string name: "String property"
    property var method: null
    property var model: null
    property var prop: null

    anchors.left: parent.left
    anchors.right: parent.right

    header.title.text: name
}
