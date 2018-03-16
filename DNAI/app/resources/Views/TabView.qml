import QtQuick 2.0
import QtQuick.Controls 2.2

import "../JavaScript/CreateComponent.js" as Factory
import "../Style"

Item {
    anchors.fill: parent
    function addView(path, data, name)
    {
        Factory.createObjects("resources/Style/MTabButton.qml", { "text" : name }, bar)
        var obj = Factory.getObject()
        bar.addItem(obj)
        Factory.createObjects(path, data, stack)
        obj = Factory.getObject()
        stack.push(obj)
    }

    MTabBar {
        id: bar
    }

    StackView {
        id: stack
        anchors.fill: parent
        anchors.topMargin: bar.height
    }
}
