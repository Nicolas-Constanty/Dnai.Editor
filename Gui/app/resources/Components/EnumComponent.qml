import QtQuick 2.0
import QtQuick.Controls 2.2

ComboBox {
    id: control
    property var modelItem: null
    property int modelIndex: 0
    onActivated: {
        modelItem.setProp(modelIndex, index)
    }
    background: Item {
    }
}
