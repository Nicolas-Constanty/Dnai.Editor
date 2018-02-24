import QtQuick 2.0
import QtQuick.Controls 1.4

import "../Style"

ExpendablePanel {
    title: "Properties"

    TableView {
        id: _tableView
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10

        TableViewColumn {
            role: "name"
            title: "Property name"
            width: _tableView.width / 3
        }
        TableViewColumn {
            role: "value"
            title: "Value"
            width: (2 * _tableView.width) / 3
        }
        model: test
        itemDelegate: Item {
            // TODO Improve this declaration with javascript creation ?
            EditableText {
                visible: styleData.column === 1
                text: styleData.value
                focus: true
            }
            MText {
                visible: styleData.column === 0
                text: styleData.value
                focus: true
            }
        }

        ListModel {
            id: test
            ListElement {
                name : "(Name)"
                value: "class1"
            }
        }
    }
}
