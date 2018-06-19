import QtQuick 2.0
import QtQuick.Controls 2.2

import DNAI 1.0
import DNAI.Enums 1.0

import Dnai.Settings 1.0
import Dnai.Controls 1.0
import Dnai.FontAwesome 1.0

import DNAI.Core 1.0

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
                model[prop] = value;
            }

            function setVariableValue(model, prop, value)
            {
                if (model.varType === 5)
                    value = '"' + value + '"'

                Controller.variable.setValue(propertyPanel.model.id, value)
            }

            function updateEnumerator(model, prop, index, value)
            {
                model[prop][index] = value
            }

            property var model: null
            width: _container.width
            ItemDelegate {
                id: _varTypeDelegate
                width: typeof(_value) === "undefined" ? 0 : _value.width
                text: typeof(model) === "undefined" ? "" : model.name
                contentItem: Text {
                   text: typeof(model) === "undefined" ? "" : model.name
                   elide: Text.ElideRight
                   verticalAlignment: Text.AlignVCenter
                }
                highlighted: typeof(control) === "undefined" ? false : control.highlightedIndex === index
            }
            onModelChanged: {
                if (propertyPanel.model === null)
                    return

                console.log('======== modèle des propriétés:', propertyPanel.model, "=========");

                for(var i = propertyPanel.children.length; i > 0 ; i--) {
                    propertyPanel.children[i-1].visible = false
                   propertyPanel.children[i-1].destroy()
                 }
                var md = propertyPanel.model
                for (var prop in md) {
                    if (prop === "name")
                    {
                        console.log("Prop name")
                        createProperty("resources/Properties/StringProperty.qml", { "value":  md[prop], "name" : prop, "model": md, "prop": prop, "method": function(model, prop, value){
                            Controller.declarator.rename(md.containerId, md.name, value);
                        } })
                    }
                    else if (prop === "visibility")
                    {
                        console.log("Prop visi")
                        createProperty("resources/Properties/DropDownProperty.qml", { "value": md[prop], "listmodel":  Editor.propertyPanelProperties.visibility, "name" : prop, "model": md, "prop": prop, "method": function(model, prop, value) {
                            console.log("Visibility:", value);
                            Controller.declarator.setVisibility(md.containerId, md.name, value);
                        } })
                    }
                    else if (prop === "entityType")
                    {
                        var val = md[prop]

                        console.log("Prop type")
                        if (val === CoreEnums.VARIABLE)
                        {
                            var t = md["guiProperties"]["varType"]

                            var varTypeView = createProperty("resources/Properties/VarTypeProperty.qml", {
                                "name": "Type",
                                "model": md
                            });

                            varTypeView.typeChanged.connect(function(newTyp){

                                Controller.variable.setType(propertyPanel.model.id, newTyp.id)

                                if (propertyPanel.propvalue === null)
                                    return;

                                if (propertyPanel.propvalue)
                                    propertyPanel.propvalue.destroy();

                                var valname = newTyp.name;

                                if (valname === "Integer")
                                {
                                    propertyPanel.propvalue = createProperty("resources/Properties/IntProperty.qml", { "value": 0, "name" : "Value", "model": model, "prop": prop, "method": setVariableValue })
                                }
                                else if (valname === "Boolean")
                                {
                                    propertyPanel.propvalue = createProperty("resources/Properties/BoolProperty.qml", { "value": false, "name" : "Value", "model": model, "prop": prop, "method": setVariableValue })
                                }
                                else
                                {
                                    propertyPanel.propvalue = createProperty("resources/Properties/StringProperty.qml", { "value": "", "name" : "Value", "model": model, "prop": prop, "method": setVariableValue })
                                }
                            });

                            var valname = Controller.getEntity(t).name;

                            if (valname === "Integer")
                            {
                                propertyPanel.propvalue = createProperty("resources/Properties/IntProperty.qml", { "value": md["guiProperties"]["value"], "name" : "Value", "model": md["guiProperties"], "prop": "value", "method": setVariableValue })
                            }
                            else if (valname === "Boolean")
                            {
                                propertyPanel.propvalue = createProperty("resources/Properties/BoolProperty.qml", { "value": md["guiProperties"]["value"], "name" : "Value", "model": md["guiProperties"], "prop": "value", "method": setVariableValue })
                            }
                            else
                            {
                                propertyPanel.propvalue = createProperty("resources/Properties/StringProperty.qml", { "value": md["guiProperties"]["value"], "name" : "Value", "model": md["guiProperties"], "prop": "value", "method": setVariableValue })
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
                            var paramView = createProperty("resources/Properties/FunctionProperty.qml", {
                                "listmodel": md["guiProperties"].inputModels,
                                "name" : "Parameters",
                                "model": md,
                                "prop": "guiProperties"
                            });
                            paramView.addValue.connect(function(){
                                var name = "param_" + Math.floor(Math.random() * 100);
                                Controller.Function.pendingParameter(md.id, name);
                                Controller.declarator.declare(md.id, 1, name);
                            });
                            paramView.deleteValue.connect(function(name){
                                Controller.Function.pendindRemoveParam(md.id, name);
                                Controller.declarator.remove(md.id, name);
                            });
                            paramView.typeChanged.connect(function(name, type){
                                var ent = md["guiProperties"].getInputId(name);
                                Controller.variable.setType(ent, type.id)
                            });
                            paramView.renamed.connect(function(name, newName){
                                Controller.declarator.rename(md.id, name, newName);
                            });
                            paramView.moveUp.connect(function(index){
                                md["guiProperties"].moveInputUp(index);
                            });
                            paramView.moveDown.connect(function(index){
                                md["guiProperties"].moveInputDown(index);
                            });

                            var retView = createProperty("resources/Properties/FunctionProperty.qml", {
                                "listmodel": md["guiProperties"].outputModels,
                                "name" : "Return",
                                "model": md,
                                "prop": "guiProperties"
                            });
                            retView.addValue.connect(function(){
                                var name = "return_" + Math.floor(Math.random() * 100);
                                Controller.Function.pendingReturn(md.id, name);
                                Controller.declarator.declare(md.id, 1, name);
                            });
                            retView.deleteValue.connect(function(name){
                                Controller.Function.pendingRmReturn(md.id, name);
                                Controller.declarator.remove(md.id, name);
                            });
                            retView.renamed.connect(function(name, newName) {
                                Controller.declarator.rename(md.id, name, newName);
                            });
                            retView.typeChanged.connect(function(name, type) {
                                var ent = md["guiProperties"].getOutputId(name);
                                Controller.variable.setType(ent, type.id);
                            });
                            retView.moveUp.connect(function(index){
                                md["guiProperties"].moveOutputUp(index)
                            });
                            retView.moveDown.connect(function(index){
                                md["guiProperties"].moveOutputDown(index)
                            });
                        }
                        else if (val === CoreEnums.OBJECT_TYPE)
                        {
                            var attrsView = createProperty("resources/Properties/AttributesProperty.qml", {
                                "model": md,
                                "name" : "Attributes"
                            });

                            attrsView.add.connect(function () {
                                Controller.Class.addAttribute(md.id, "Attribute" + Math.floor(Math.random() * 100), 2, CoreEnums.PUBLIC);
                            });
                            attrsView.remove.connect(function (attrname) {
                                Controller.Class.removeAttribute(md.id, attrname);
                            });
                            attrsView.rename.connect(function (currname, newname) {
                                Controller.Class.renameAttribute(md.id, currname, newname);
                            });
                            attrsView.changeType.connect(function (name, vartype) {
                                Controller.Class.setAttributeType(md.id, name, vartype);
                            });

                            var funcView = createProperty("resources/Properties/ClassFunctionsProperty.qml",
                                                          {
                                                              "model": md,
                                                              "name": "Functions"
                                                          });
                            funcView.setFunctionStatus.connect(function(name, member){
                                console.log("Set function ", name, " status to ", member ? "member" : "static");
                                if (member)
                                    Controller.Class.setFunctionAsMember(md.id, name);
                                else
                                    Controller.Class.setFunctionAsStatic(md.id, name);
                            });
                        }
                    }
                }
            }
            Component.onCompleted: {
                Editor.registerPropertyView(propertyPanel);
            }
        }
    }
}
