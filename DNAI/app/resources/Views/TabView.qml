import QtQuick 2.0
import QtQuick.Controls 2.2
import DNAI 1.0

import "../JavaScript/CreateComponent.js" as Factory
import "../Style"

Item {
    anchors.fill: parent
    function addView(path, data, name)
    {

        Factory.createObjects("resources/Style/MTabButton.qml", { "text" : name,}, _bar)
        var obj = Factory.getObject()
        _bar.addItem(obj)

        Factory.createObjects(path, data, _swip)
        obj = Factory.getObject()
        _swip.addItem(obj)
        Editor.selectView(obj);
    }

    function selectIndex(index)
    {
        _bar.setCurrentIndex(index)
        _swip.setCurrentIndex(index)
    }

    MTabBar {
        id: _bar
        currentIndex: _swip.currentIndex
        onCurrentIndexChanged: {
            _swip.currentIndex = currentIndex
        }
    }

    SwipeView {
        id: _swip
        currentIndex: _bar.currentIndex
        anchors.fill: parent
        anchors.topMargin: _bar.height
        padding: 0
        onCurrentIndexChanged: {
           _bar.currentIndex = currentIndex
       }
    }
}
