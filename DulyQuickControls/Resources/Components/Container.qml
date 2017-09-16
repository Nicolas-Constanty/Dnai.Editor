import QtQuick 2.9

Item {
    property alias innerElement : content.sourceComponent

    Loader { id: content }
}
