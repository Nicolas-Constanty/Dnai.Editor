import QtQuick 2.0
import QtQuick.Controls 2.2

import DNAI 1.0
import DNAI.Core 1.0

ComboBox {
    id: __this__

    property var typeGuid

    signal typeChanged(var typeId, var newTypeId)

    model: Editor.propertyPanelProperties.varTypes
    textRole: "name"

    font.pointSize: 8

    function getModelType()
    {
        return Controller.getEntity(typeGuid);
    }

    function getBoxType()
    {
        var id = Editor.propertyPanelProperties.varTypes.getValueFromIndex(currentIndex);

        return Controller.getEntity(id);
    }

    function getModelIndex()
    {
        return Editor.propertyPanelProperties.varTypes.getIndexFromValue(getModelType().id);
    }

    currentIndex: getModelIndex()

    onCurrentIndexChanged: {
        var boxType = getBoxType();
        var modelType = getModelType();

        if (modelType.guid !== boxType.guid)
            __this__.typeChanged(modelType.id, boxType.id);
    }
}
