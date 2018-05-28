import QtQuick 2.0
import QtQuick.Controls 1.4

import DNAI 1.0
import DNAI.Enums 1.0

import Dnai.Controls 1.0
import Dnai.FontAwesome 1.0

import "../Style"
import "../Properties"
import "../JavaScript/CreateComponent.js" as Factory

Rectangle {
    id: _container
    anchors.fill: parent
    color: "#16ffffff"
    property string title: "Property panel"
    property real rowheight: 16
    property var last: null

    function debugModel(md)
    {
        for (var p in md)
            console.log(p, md[p])
    }

    ScrollView {
        anchors.fill: parent
        Column {
            id: propertyPanel
            property var propvalue: null
            function createProperty(path, ctor)
            {
                var obj = null
                Factory.createObjects(path, ctor, propertyPanel)
                obj = Factory.getObject()
                obj.anchors.left = obj.parent.left
                obj.anchors.right = obj.parent.right
                obj.anchors.margins = 10
                return obj
            }

            function updateProp(model, prop, value)
            {
                console.log(model, prop, value)
                model[prop] = value
            }

            function updatePropType(model, prop, value)
            {
                model[prop] = value
                if (propertyPanel.propvalue === null)
                    return;
                propertyPanel.propvalue.destroy()
                if (value === 0)
                {
                    propertyPanel.propvalue = createProperty("resources/Properties/IntProperty.qml", { "value": 0, "name" : "Value", "model": model, "prop": prop, "method": updateProp })
                }
                else if (value === 1)
                {
                    propertyPanel.propvalue = createProperty("resources/Properties/BoolProperty.qml", { "value": false, "name" : "Value", "model": model, "prop": prop, "method": updateProp })
                }
                else if (value === 2)
                {
                    propertyPanel.propvalue = createProperty("resources/Properties/StringProperty.qml", { "value": "", "name" : "Value", "model": model, "prop": prop, "method": updateProp })
                }
            }

            function updateEnumerator(model, prop, index, value)
            {
                model[prop][index] = value
            }

            property var model: null
            width: _container.width
            onModelChanged: {
                if (propertyPanel.model === null)
                    return

                console.log('======== modèle des propriétés:', propertyPanel.model, "=========");

                for(var i = propertyPanel.children.length; i > 0 ; i--) {
                   propertyPanel.children[i-1].destroy()
                 }
                var md = propertyPanel.model
                for (var prop in md) {
                    if (prop === "name")
                    {
                        createProperty("resources/Properties/StringProperty.qml", { "value":  md[prop], "name" : prop, "model": md, "prop": prop, "method": updateProp })
                    }
                    else if (prop === "visibility")
                    {
                        createProperty("resources/Properties/DropDownProperty.qml", { "value": md[prop], "listmodel":  Editor.propertyPanelProperties.visibility, "name" : prop, "model": md, "prop": prop, "method": updateProp })
                    }
                    else if (prop === "entityType")
                    {
                        var val = md[prop]
                        if (val === CoreEnums.VARIABLE)
                        {
                            var t = md["guiProperties"]["varType"]
                            createProperty("resources/Properties/DropDownProperty.qml", { "value": t, "listmodel": Editor.propertyPanelProperties.varType, "name" : "Type", "model": md["guiProperties"], "prop": "value", "method": updatePropType})
                            if (t === 0)
                            {
                                propertyPanel.propvalue = createProperty("resources/Properties/IntProperty.qml", { "value": md["guiProperties"]["value"], "name" : "Value", "model": md["guiProperties"], "prop": "value", "method": updateProp })
                            }
                            else if (t === 1)
                            {
                                propertyPanel.propvalue = createProperty("resources/Properties/BoolProperty.qml", { "value": md["guiProperties"]["value"], "name" : "Value", "model": md["guiProperties"], "prop": "value", "method": updateProp })
                            }
                            else if (t === 2)
                            {
                                propertyPanel.propvalue = createProperty("resources/Properties/StringProperty.qml", { "value": md["guiProperties"]["value"], "name" : "Value", "model": md["guiProperties"], "prop": "value", "method": updateProp })
                            }
                        }
                        else if (val === CoreEnums.ENUM_TYPE)
                        {
                            createProperty("resources/Properties/EnumerationProperty.qml",
                                           {
                                               "listmodel": md["guiProperties"]["values"],
                                               "name" : "Values",
                                               "model": md["guiProperties"],
                                               "prop": "values",
                                               "method": updateEnumerator,
                                               "entityID": propertyPanel.model.id
                                           })
                        }
                        else if (val === CoreEnums.FUNCTION)
                        {
                            createProperty("resources/Properties/FunctionProperty.qml",
                                           {
                                               "listmodel": md["guiProperties"].inputModels,
                                               "name" : "Parameters",
                                               "model": md,
                                               "prop": "guiProperties",
                                               "addValue": function () {
                                                   md["guiProperties"].addInput("", 0)
                                               },
                                               "moveUp" : function (idx)
                                               {
                                                   md["guiProperties"].moveInputUp(idx)
                                               },
                                               "moveDown" : function (idx)
                                               {
                                                   md["guiProperties"].moveInputDown(idx)
                                               },
                                               "deleteValue": function (val)
                                               {
                                                   md["guiProperties"].removeInput(val)
                                               },
                                               "nameChanged": function (idx, val)
                                               {
                                                   md["guiProperties"].updateInputName(idx, val)
                                               },
                                               "typeChanged": function (idx, val)
                                               {
                                                   md["guiProperties"].updateInputVarType(idx, val)
                                               }
                                           })
                            createProperty("resources/Properties/FunctionProperty.qml",
                                           {
                                               "listmodel": md["guiProperties"].outputModels,
                                               "name" : "Return",
                                               "model": md,
                                               "prop": "guiProperties",
                                               "addValue": function () {
                                                   md["guiProperties"].addOutput("", 0)
                                               },
                                               "moveUp" : function (idx)
                                               {
                                                   md["guiProperties"].moveOutputUp(idx)
                                               },
                                               "moveDown" : function (idx)
                                               {
                                                   md["guiProperties"].moveOutputDown(idx)
                                               },
                                               "deleteValue": function (val)
                                               {
                                                   md["guiProperties"].removeOutput(val)
                                               },
                                               "nameChanged": function (idx, val)
                                               {
                                                   md["guiProperties"].updateOutputName(idx, val)
                                               },
                                               "typeChanged": function (idx, val)
                                               {
                                                   md["guiProperties"].updateOutputVarType(idx, val)
                                               }
                                           })
                        }
                    }
                    //print(prop += " (" + typeof(md[prop]) + ") = " + md[prop]);
                }
            }
            Component.onCompleted: {
                Editor.registerPropertyView(propertyPanel);
            }

        }
    }


//    MLabel {
//        id: _title
//        height: 35
//        padding: 15
//        text: title
//        color: "#CCFFFFFF"
//        font.family: "segoeuisl"
//        font.pointSize: 10
//        font.capitalization: Font.AllUppercase
//        anchors.left: parent.left
//        anchors.top: parent.top
//    }

//    SplitView {
//        id: propertyView
//        anchors.top: _title.bottom
//        anchors.bottom: parent.bottom
//        anchors.left: parent.left
//        anchors.right: parent.right
//        orientation: Qt.Horizontal
//        property alias model: propertiesNameList.model

//        Column {
//            id: propertiesName
//            width: propertyView.width / 2
//            anchors.left: parent.left
//            property real rectangleHeight: 0
//            Repeater {
//                id: propertiesNameList
//                MLabel {
//                    id: labelText
//                    anchors.left: parent.left
//                    anchors.right: parent.right
//                    text: qsTr(model.name)
//                    padding: 3
//                    leftPadding: 4
//                    horizontalAlignment: Text.AlignLeft
//                    font.capitalization: Font.Capitalize
//                    font.pointSize: 8
//                    Rectangle {
//                        anchors.left: parent.left
//                        anchors.right: parent.right
//                        anchors.bottom: parent.bottom
//                        height: 1
//                        color: AppSettings.theme["border"]["color"]
//                    }
//                    Component.onCompleted: {
//                        propertiesName.rectangleHeight = labelText.height
//                    }
//                }
//            }
//        }
//        Column {
//            id: propertiesValue
//            anchors.left: propertiesName.right
//            anchors.right: parent.right
//            Repeater {
//                model: propertiesNameList.model
//                Rectangle {
//                    id: value
//                    anchors.left: parent.left
//                    anchors.right: parent.right
//                    height: propertiesName.rectangleHeight
//                    color: "transparent"
//                    Rectangle {
//                        anchors.left: parent.left
//                        anchors.right: parent.right
//                        anchors.bottom: parent.bottom
//                        height: 1
//                        color: AppSettings.theme["border"]["color"]
//                    }
//                    Component.onCompleted: {
//                        var obj
//                        if (model.name === "visibility")
//                        {
//                            Factory.createObjects("resources/Components/EnumComponent.qml",
//                                                  {
//                                                      "model" : Editor.propertyPanelProperties.visibility,
//                                                      "modelIndex" : index,
//                                                      "modelItem" : model.item
//                                                  }, value)
//                            obj = Factory.getObject()
//                            obj.currentIndex = model.value
//                            obj.anchors.fill = value
//                        }
//                        else if (model.name === "entityType")
//                        {
//                            Factory.createObjects("resources/Components/EnumComponent.qml",
//                                                  {
//                                                      "model" : Editor.propertyPanelProperties.entityType,
//                                                      "modelIndex" : index,
//                                                      "modelItem" : model.item
//                                                  }, value)
//                            obj = Factory.getObject()
//                            obj.currentIndex = model.value
//                            obj.anchors.fill = value
//                        }
//                        else if (model.name === "varType")
//                        {
//                            Factory.createObjects("resources/Components/EnumComponent.qml",
//                                                  {
//                                                      "model" : Editor.propertyPanelProperties.varType,
//                                                      "modelIndex" : index,
//                                                      "modelItem" : model.item
//                                                  }, value)
//                            obj = Factory.getObject()
//                            obj.currentIndex = model.value
//                            obj.anchors.fill = value
//                        }
//                        else
//                        {
//                            Factory.createObjects("resources/Components/EditableTextModel.qml",
//                                                  {
//                                                      "text" : model.value,
//                                                      "index" : index,
//                                                      "model" : model.item
//                                                  }, value)
//                            obj = Factory.getObject()
//                            obj.anchors.fill = value
//                        }
//                    }
//                }
//            }
//        }
//        Component.onCompleted: {
//            Editor.registerPropertyView(propertyView);
//        }
//    }


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
//            backgroundColor :  AppSettings.theme["background"]["darkColor"]
//            alternateBackgroundColor:  AppSettings.theme["background"]["darkColor"]
//            highlightedTextColor: AppSettings.theme["background"]["color"]
//            textColor : AppSettings.theme["text"]["color"]
//        }
//            itemDelegate: Rectangle {
//                color: AppSettings.theme["background"]["darkColor"]
//                // TODO Improve this declaration with javascript creation ?
//                EditableText {
//                    id: editText
//                    visible: styleData.column === 1 && typeof(styleData.value) === "string"
//                    text: styleData.value
//                    focus: true
//                    color: AppSettings.theme["text"]["color"]
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
//                   color: AppSettings.theme["border"]["color"]
//                }
//                Rectangle {
//                    y: -1
//                    anchors{
//                        right: parent.right
//                        left: parent.left
//                        bottom: parent.bottom
//                    }
//                    height: 1
//                    color: AppSettings.theme["border"]["color"]
//                }
//            }
//        Component.onCompleted: {
//            Editor.registerPropertyView(propertyView);
//        }
//    }
}
