import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4

import DNAI 1.0
import "../Style"

Panel {
    id: panel
    ListView {
        id: view
        anchors.fill: parent
        orientation: Qt.Horizontal
        spacing: -2
        interactive: false
//        model: Manager.views.namespacebarModel
        delegate: Item {
            id: rootItem
            width: button.width + (model.modelData.asChild ? button1.width : 1)
            Button {
                id: button
                height: view.height
                contentItem: MText {
                    text: model.modelData.path
                }
                background: Rectangle {
                    id: back
                    color: button.pressed ? AppSettings.style.background.darkColor : button.hovered ? AppSettings.style.background.lightColor : "transparent"
                    border.color: AppSettings.style.border.color
                }
                onClicked: {
//                    Manager.views.treeView().changeCurrent(model.modelData.model)
                }
            }
            Button {
                id: button1
                anchors.left: button.right
                anchors.leftMargin: -1
                height: view.height
                contentItem: MText {
                    text: ">"
                }
                background: Rectangle {
                    id: back1
                    color: button1.pressed ? AppSettings.style.background.darkColor : button1.hovered ? AppSettings.style.background.lightColor : "transparent"
                    border.color: AppSettings.style.border.color
                }
                visible: model.modelData.asChild
            }
        }
    }
}
