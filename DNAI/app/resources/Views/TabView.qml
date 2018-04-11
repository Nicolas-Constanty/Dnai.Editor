import QtQuick 2.0
import QtQuick.Controls 2.2
import DNAI 1.0

import "../JavaScript/CreateComponent.js" as Factory
import "../Style"

Item {
    id: view
    anchors.fill: parent
    property var listModel: ({});
    property int localindex: -1
    property Item currentView: null
    function addView(path, data, name)
    {
        Factory.createObjects("resources/Style/MTabButton.qml", {
                                  "text" : name,
                                  "tb" : _bar,
                                  "sv" : _swip
                              }, _bar)
        var obj = Factory.getObject()
        _bar.addItem(obj)
        Factory.createObjects(path, data, _swip)
        var obj1 = Factory.getObject()
        _swip.addItem(obj1)
        Editor.selectView(view)
        obj.refContent = obj1
        _bar.setCurrentIndex(_bar.count - 1)
        localindex += 1
        return localindex
    }

    function appendModel(model, viewindex)
    {
        listModel[model] = viewindex
    }

    function getViewFromModel(model)
    {
        return listModel[model]
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
            currentView = _swip.itemAt(currentIndex)
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
           currentView = _swip.itemAt(currentIndex)
       }
        onWidthChanged: {
            console.log(width)
        }
    }
}
