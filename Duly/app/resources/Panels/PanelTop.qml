import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import Utils 1.0

Panel {
    id: panel
    ListView {
        id: view
        anchors.fill: parent
        orientation: Qt.Horizontal
        spacing: -2
        interactive: false
        model: Manager.namespacebarModel
        delegate: Item {
            id: rootItem
            width: button.width + (model.modelData.asChild ? button1.width : 1)
            Button {
                id: button
                height: view.height
                contentItem: Text {
                    text: model.modelData.path
                    color: DulySettings.style.text.color
                    font.family: DulySettings.style.font.family
                }
                background: Rectangle {
                    id: back
                    color: button.pressed ? DulySettings.style.delegateColor : button.hovered ? DulySettings.style.alternateBackground : "transparent"
                    border.color: DulySettings.style.border.color
                }
                onClicked: {
                    appWindow.layout.leftPanel.treeview.changeCurrent(model.modelData.idx)
                }
            }
            Button {
                id: button1
                anchors.left: button.right
                anchors.leftMargin: -1
                height: view.height
                contentItem: Text {
                    text: ">"
                    color: DulySettings.style.text.color
                    font.family: DulySettings.style.font.family
                }
                background: Rectangle {
                    id: back1
                    color: button1.pressed ? DulySettings.style.delegateColor : button1.hovered ? DulySettings.style.alternateBackground : "transparent"
                    border.color: DulySettings.style.border.color
                }
                visible: model.modelData.asChild
            }
        }
    }
}
