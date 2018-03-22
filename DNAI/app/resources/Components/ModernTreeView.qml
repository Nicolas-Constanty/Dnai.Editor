import QtQuick 2.0

import "../Style"
import "../JavaScript/CreateComponent.js" as Factory

ListView {
    id: _view
    property alias model: _view.model
    property int level: 0
    property int indentation: 10
    property Item itemdelegate: null
    QtObject {
        id: internal
        property int _indentation: _view.level * _view.indentation
    }
    anchors.leftMargin: internal._indentation
    delegate: Item {
        id: _idel
        Component.onCompleted: {
            if (itemdelegate !== null)
                itemdelegate.parent = _view
            if (item !== null)
            {
                Factory.createObjects("resources/Components/ModernTreeView.qml", {
                                          "level" : _view.level + 1,
                                          "delegate" : item
                                      }, _idel)

            }
        }
    }
}
