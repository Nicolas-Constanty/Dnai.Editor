import QtQuick 2.0
import QtQuick.Controls 2.2
import DNAI 1.0
import DNAI.Core 1.0

import "../JavaScript/CreateComponent.js" as Factory
import "../Style"

Item {
    id: view
    anchors.fill: parent
    property var listModel: ({});
    property int localindex: -1
    property Item currentView: null
    property alias bar: _bar
    property alias swip: _swip

    function addView(path, data, name, ref)
    {
        Factory.createObjects("resources/Style/MTabButton.qml", {
                                  "text" : name,
                                  "tv" : view
                              }, _bar)
        var obj = Factory.getObject()
        _bar.addItem(obj)
        obj.anchors.top = obj.parent.top
        obj.anchors.bottom = obj.parent.bottom
        Factory.createObjects(path, data, _swip)
        var v = Factory.getObject()
        _swip.addItem(v)
        Editor.selectView(view)
        obj.refContent = v
        _bar.setCurrentIndex(_bar.count - 1)
        return v
    }

    function appendModel(model, viewref)
    {
        listModel[model] = viewref
    }

    function getViewFromModel(model)
    {
        for (var i = 0; i < _bar.count; i++)
        {
            if (_swip.itemAt(i) === listModel[model])
                return i;
        }
        return -1
    }

    function removeViewFromModel(model)
    {
        for (var i = 0; i < _bar.count; i++) {
            if (_bar.itemAt(i).refContent === listModel[model])
            {
                _bar.itemAt(i).close();
                break;
            }
        }
    }

    function removeView(v)
    {
        for (var keyModel in listModel)
        {
            if (listModel[keyModel] === v)
            {
                delete listModel[keyModel]
                break
            }
        }
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
            //console.log("Curr index changed in bar: ", currentIndex);
            _swip.currentIndex = currentIndex
            currentView = _swip.itemAt(currentIndex)
        }
    }

    SwipeView {
        id: _swip
        interactive: false
        currentIndex: _bar.currentIndex
        anchors.fill: parent
        anchors.topMargin: _bar.height
        padding: 0
        onCurrentIndexChanged: {
            //console.log("Curr index changed in swip: ", currentIndex);
           _bar.currentIndex = currentIndex
           currentView = _swip.itemAt(currentIndex)
       }
    }

    Connections {
        target: Controller.declarator
        onRemoved : {
            removeViewFromModel(entity)
        }
    }
}
