import QtQuick 1.1

Item {
    property alias innerElement : content.sourceComponent

    Loader { id: content }
}
