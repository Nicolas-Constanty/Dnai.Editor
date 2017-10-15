import QtQuick 2.4
import QtQuick.Controls 2.0
import "../Forms"
import DulyUtils 1.0



ConsoleForm {
    title: "Console"
    consoleRef.onCountChanged: {
        consoleRef.positionViewAtEnd()
    }
    consoleListDelegate: Rectangle {
        height: 25
        color: "transparent"
        width: parent.width
        Label {
            text: if (modelData.substring(0, 2) === "[#")
                  {
                        color = modelData.substring(1, 8)
                        modelData.slice(9)
                  }
            else
                modelData
        }
    }
}
