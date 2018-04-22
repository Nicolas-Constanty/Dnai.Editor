import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

import DNAI 1.0
import "../Style"

Rectangle {
    anchors.fill: parent
    color: "#16ffffff"
    property string title: "Property panel"
    property real rowheight: 16
    property var last: null
    MLabel {
        id: _title
        height: 35
        padding: 15
        text: title
        color: "#CCFFFFFF"
        font.family: "segoeuisl"
        font.pointSize: 10
        font.capitalization: Font.AllUppercase
        anchors.left: parent.left
        anchors.top: parent.top
    }
    TableView {
        id: propertyView
        anchors.top: _title.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        TableViewColumn {
            role: "name"
            title: "Property name"
            width: propertyView.width / 3
        }
        TableViewColumn {
            role: "value"
            title: "Value"
            width: (2 * propertyView.width) / 3
        }
        frameVisible: false
        headerVisible: false
        style: TableViewStyle {
            backgroundColor :  AppSettings.style.background.darkColor
            alternateBackgroundColor:  AppSettings.style.background.darkColor
            highlightedTextColor: AppSettings.style.background.color
            textColor : AppSettings.style.text.color
        }
            itemDelegate: Rectangle {
                color: AppSettings.style.background.darkColor
                // TODO Improve this declaration with javascript creation ?
                EditableText {
                    id: editText
                    visible: styleData.column === 1
                    text: styleData.value
                    focus: true
                    color: AppSettings.style.text.color
                    onAccepted: {
                        propertyView.model.model().setProp(styleData.row, editText.text)
                    }
                }
                MText {
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
                   color: AppSettings.style.border.color
                }
                Rectangle {
                    y: -1
                    anchors{
                        right: parent.right
                        left: parent.left
                        bottom: parent.bottom
                    }
                    height: 1
                    color: AppSettings.style.border.color
                }
            }
        Component.onCompleted: {
            Editor.registerPropertyView(propertyView);
        }
    }
}
