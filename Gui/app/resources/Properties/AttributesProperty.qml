import QtQuick 2.0
import QtQuick.Controls 2.2

import DNAI 1.0
import Dnai.FontAwesome 1.0
import DNAI.Core 1.0

import "../Style"

BaseProperty {
    id: __this__

    property int attributeHeight: 30

    signal add()
    signal remove(string name)
    signal rename(string name, string newname)
    signal changeType(string name, int vartypeIndex)

    anchors.left: parent.left
    anchors.right: parent.right

    height: header.height + 100 + __add__.height

    /*
     * List view
     */
    ListView {
        id: __attributes__
        model: __this__.model ? __this__.model.guiProperties.attributes : []

        anchors.left: parent.left
        anchors.right: parent.right
        height: model.length * __this__.attributeHeight

        delegate: Row {

            width: parent.width
            height: __this__.attributeHeight

            spacing: 2

            /*
             * Attribute name
             */
            EditableText {
                id: __name__

                width: (parent.width - __remove__.width) * 0.5
                height: parent.height

                text: modelData

                font.pointSize: 8

                onAccepted: {
                    __this__.rename(modelData, __name__.text);
                }
            }

            /*
             * Attribute type
             */
            ComboBox {
                id: __type__

                width: (parent.width - __remove__.width) * 0.5
                height: parent.height

                model: Editor.propertyPanelProperties.varTypes
                textRole: "name"

                font.pointSize: 8

                function getModelType()
                {
                    if (__this__.model)
                        return Controller.getEntity(__this__.model.guiProperties.getAttribute(modelData)).id;
                    return 2;
                }

                function getBoxType()
                {
                    return Editor.propertyPanelProperties.varTypes.getValueFromIndex(currentIndex);
                }

                function getModelIndex()
                {
                    return Editor.propertyPanelProperties.varTypes.getIndexFromValue(getModelType());
                }

                currentIndex: getModelIndex()

                onCurrentIndexChanged: {
                    if (getBoxType() === __this__.model.id)
                    {
                        Editor.notifyError("Cannot set an attribute of the type of the object");
                        currentIndex = getModelIndex();
                    }
                    else if (getModelType() !== getBoxType())
                        __this__.changeType(modelData, getBoxType());
                }
            }

            /*
             * Attribute remove
             */
            ButtonAwesomeSolid {
                id: __remove__

                width: 40
                height: parent.height

                label.text: "\uf2ed"

                font.pointSize: 8

                onClicked: {
                    __this__.remove(__name__.text);
                }
            }
        }
    }

    /*
     * Button to add
     */
    ButtonAwesomeSolid {
        id: __add__

        anchors.left: parent.left
        anchors.right: parent.right

        label.text: "\uf055"

        Component.onCompleted: {
            console.log("Attributes button: Dim(", width, "x", height, ")");
        }

        onClicked: {
            __this__.add();
        }
    }
}
