import QtQuick 2.0
import QtQuick.Controls 2.2

import "../Style"

Item {
    id: _control
    property alias content: _content.content
    property alias contentItem: _content

    property string text: "Item"
    height: 40
    MLabel {
        anchors.left: parent.left
        height: parent.height
        text: qsTr(_control.text)
        verticalAlignment: "AlignVCenter"
    }
    Item {
        id: _content
        height: parent.height
        anchors.right: parent.right
        property Component content: null
        onContentChanged: {
            if (content !== null)
            {
                _loader.sourceComponent = content
            }
        }
        Loader {
           id: _loader
           height: parent.height
           anchors.right: parent.right
        }
    }
}
