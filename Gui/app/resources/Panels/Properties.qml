import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

import DNAI 1.0
import DNAI.Models 1.0
import Dnai.Theme 1.0

import "../Style"

ExpendablePanel {
    title: "Properties"

    TableView {
        id: _tableView
        anchors.fill: parent
        anchors.rightMargin: -2
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
        frameVisible: false
        headerVisible: false
        style: TableViewStyle {
            backgroundColor :  AppSettings.theme["colors"]["background"]["dark"]
            alternateBackgroundColor:  AppSettings.theme["colors"]["background"]["dark"]
            highlightedTextColor: AppSettings.theme["colors"]["background"]["base"]
            textColor : AppSettings.theme["text"]["color"]
        }

//        model: Manager.views.propertyPanelModel
        itemDelegate: Rectangle {
            color: AppSettings.theme["colors"]["background"]["dark"]
            // TODO Improve this declaration with javascript creation ?
            TextField {
                visible: styleData.column === 1
                text: styleData.value
                focus: true
                color: AppSettings.theme["text"]["color"]
            }
            Label {
                visible: styleData.column === 0
                text: styleData.value
                focus: true
            }
            Rectangle {
                anchors {
                   right: parent.right
                   top: parent.top
                   bottom: parent.bottom
               }
               width: 1
               color: AppSettings.theme["border"]["color"]
            }
            Rectangle {
                y: -1
                anchors{
                    right: parent.right
                    left: parent.left
                    bottom: parent.bottom
                }
                height: 1
                color: AppSettings.theme["border"]["color"]
            }
        }

//        ListModel {
//            id: test
//            ListElement {
//                name : "(Name)"
//                value: "class1"
//            }
//        }
    }
}
