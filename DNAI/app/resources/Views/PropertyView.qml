import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4

import DNAI 1.0
import DNAI.Enums 1.0
import "../Style"
import "../JavaScript/CreateComponent.js" as Factory

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

    SplitView {
        id: propertyView
        anchors.top: _title.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        orientation: Qt.Horizontal
        property alias model: propertiesNameList.model

        Column {
            id: propertiesName
            width: propertyView.width / 2
            anchors.left: parent.left
            property real rectangleHeight: 0
            Repeater {
                id: propertiesNameList
                MLabel {
                    id: labelText
                    anchors.left: parent.left
                    anchors.right: parent.right
                    text: qsTr(model.name)
                    padding: 3
                    leftPadding: 4
                    horizontalAlignment: Text.AlignLeft
                    font.capitalization: Font.Capitalize
                    font.pointSize: 8
                    Rectangle {
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
                        height: 1
                        color: AppSettings.style.border.color
                    }
                    Component.onCompleted: {
                        propertiesName.rectangleHeight = labelText.height
                    }
                }
            }
        }
        Column {
            id: propertiesValue
            anchors.left: propertiesName.right
            anchors.right: parent.right
            Repeater {
                model: propertiesNameList.model
                Rectangle {
                    id: value
                    anchors.left: parent.left
                    anchors.right: parent.right
                    height: propertiesName.rectangleHeight
                    color: "transparent"
                    Rectangle {
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
                        height: 1
                        color: AppSettings.style.border.color
                    }
                    Component.onCompleted: {
                        var obj
                        if (model.name === "visibility")
                        {
                            Factory.createObjects("resources/Components/EnumComponent.qml",
                                                  {
                                                      "model" : Editor.propertyPanelProperties.visibility,
                                                      "modelIndex" : index,
                                                      "modelItem" : model.item
                                                  }, value)
                            obj = Factory.getObject()
                            obj.currentIndex = model.value
                            obj.anchors.fill = value
                        }
                        else if (model.name === "entityType")
                        {
                            Factory.createObjects("resources/Components/EnumComponent.qml",
                                                  {
                                                      "model" : Editor.propertyPanelProperties.entityType,
                                                      "modelIndex" : index,
                                                      "modelItem" : model.item
                                                  }, value)
                            obj = Factory.getObject()
                            obj.currentIndex = model.value
                            obj.anchors.fill = value
                        }
                        else
                        {
                            Factory.createObjects("resources/Components/EditableTextModel.qml",
                                                  {
                                                      "text" : model.value,
                                                      "index" : index,
                                                      "model" : model.item
                                                  }, value)
                            obj = Factory.getObject()
                            obj.anchors.fill = value
                        }
                    }
                }
            }
        }
        Component.onCompleted: {
            Editor.registerPropertyView(propertyView);
        }
    }


//    TableView {
//        id: propertyView
//        anchors.top: _title.bottom
//        anchors.bottom: parent.bottom
//        anchors.left: parent.left
//        anchors.right: parent.right
//        TableViewColumn {
//            role: "name"
//            title: "Property name"
//            width: propertyView.width / 3
//        }
//        TableViewColumn {
//            role: "value"
//            title: "Value"
//            width: (2 * propertyView.width) / 3
//        }
//        frameVisible: false
//        headerVisible: false
//        style: TableViewStyle {
//            backgroundColor :  AppSettings.style.background.darkColor
//            alternateBackgroundColor:  AppSettings.style.background.darkColor
//            highlightedTextColor: AppSettings.style.background.color
//            textColor : AppSettings.style.text.color
//        }
//            itemDelegate: Rectangle {
//                color: AppSettings.style.background.darkColor
//                // TODO Improve this declaration with javascript creation ?
//                EditableText {
//                    id: editText
//                    visible: styleData.column === 1 && typeof(styleData.value) === "string"
//                    text: styleData.value
//                    focus: true
//                    color: AppSettings.style.text.color
//                    onAccepted: {
//                        propertyView.model.model().setProp(styleData.row, editText.text)
//                    }
//                }

//                MText {
//                    visible: styleData.column === 0
//                    text: styleData.value
//                    focus: true
//                }
//                Rectangle {
//                    anchors {
//                       right: parent.right
//                       top: parent.top
//                       bottom: parent.bottom
//                   }
//                   width: 1
//                   color: AppSettings.style.border.color
//                }
//                Rectangle {
//                    y: -1
//                    anchors{
//                        right: parent.right
//                        left: parent.left
//                        bottom: parent.bottom
//                    }
//                    height: 1
//                    color: AppSettings.style.border.color
//                }
//            }
//        Component.onCompleted: {
//            Editor.registerPropertyView(propertyView);
//        }
//    }
}
