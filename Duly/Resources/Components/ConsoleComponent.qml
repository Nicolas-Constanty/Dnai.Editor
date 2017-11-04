import QtQuick 2.4
import QtQuick.Controls 2.0
import "../Forms"
import DulyUtils 1.0

ConsoleForm {
    property int startPos: y
    id: consoleForm
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
    consoleMode.onCurrentIndexChanged: {
        if (consoleMode.currentIndex == Console.Normal)
            consoleRefMode.mode = Console.Normal
        else if (consoleMode.currentIndex == Console.Verbose)
            consoleRefMode.mode = Console.Verbose
    }
    states: [
        State{
            name: "Visible"
            PropertyChanges{target: consoleForm; y: startPos }
            PropertyChanges{target: consoleForm; visible: true}
        },
        State{
            name:"Invisible"
            PropertyChanges{target: consoleForm; y: startPos + height }
            PropertyChanges{target: consoleForm; visible: false}
        }
    ]
    state: "Visible"
    transitions: [
            Transition {
                from: "Visible"
                to: "Invisible"

                SequentialAnimation{
                   NumberAnimation {
                       target: consoleForm
                       property: "y"
                       duration: 500
                       easing.type: Easing.InOutQuad
                   }
                   NumberAnimation {
                       target: consoleForm
                       property: "visible"
                       duration: 0
                   }
                }
            },
            Transition {
                from: "Invisible"
                to: "Visible"
                SequentialAnimation{
                   NumberAnimation {
                       target: consoleForm
                       property: "visible"
                       duration: 0
                   }
                   NumberAnimation {
                       target: consoleForm
                       property: "y"
                       duration: 500
                       easing.type: Easing.InOutQuad
                   }
                }
            }
        ]
}
