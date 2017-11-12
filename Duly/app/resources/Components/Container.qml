import QtQuick 2.9
import CustomGeometry 1.0

Item {
    property alias borderColor: rect.borderColor
    property alias refRect: rect
    property alias model: list.model
    property alias delegate: list.delegate
    RoundedRectangle {
        id: rect
        borderWidth: 2
        ListView {
            id: list
        }
    }
}
