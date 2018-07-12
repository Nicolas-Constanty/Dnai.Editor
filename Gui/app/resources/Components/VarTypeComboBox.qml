import QtQuick 2.0
import QtQuick.Controls 2.2

import DNAI 1.0
import DNAI.Core 1.0
import Dnai.Theme 1.0

ComboBox {
    id: __this__

    property var typeGuid

    signal typeChanged(var newType)

    model: Controller.types
    textRole: "name"

    font.pointSize: 8

    currentIndex: Controller.getTypeIndex(typeGuid)

    function resetIndex()
    {
        currentIndex = Controller.getTypeIndex(typeGuid);
    }

    onTypeGuidChanged: {
        resetIndex();
    }

    onCurrentIndexChanged: {
        __this__.typeChanged(Controller.getType(currentIndex));
    }
}
