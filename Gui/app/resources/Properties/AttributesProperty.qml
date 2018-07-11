import QtQuick 2.0
import QtQuick.Controls 2.2

import DNAI 1.0
import Dnai.FontAwesome 1.0
import DNAI.Core 1.0
import Dnai.Theme 1.0

import "../Components"

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
            id: _row
            width: parent.width
            height: __this__.attributeHeight

            spacing: 4

            /*
             * Attribute type
             */
            VarTypeComboBox {
                id: __type__

                typeGuid: __this__.model ? __this__.model.guiProperties.getAttribute(modelData) : 0

                anchors.verticalCenter: parent.verticalCenter

                onTypeChanged: {
                    if (newType.id === __this__.model.id)
                    {
                        Editor.notifyError("Cannot set an attribute of the type of the object");
                        __type__.resetIndex();
                    }
                    else if (newType.guid !== __this__.model.guiProperties.getAttribute(modelData))
                    {
                        __this__.changeType(modelData, newType.id);
                    }
                }
            }

            /*
             * Attribute name
             */
            TextField {
                id: __name__

                width: parent.width - 2 * _row.spacing - __type__.width - __remove__.width
                height: 26
                anchors.verticalCenter: parent.verticalCenter

                text: modelData

                font.pointSize: 8

                onAccepted: {
                    __this__.rename(modelData, __name__.text);
                }
            }

            /*
             * Attribute remove
             */
            Button {
                id: __remove__

                height: parent.height

                topPadding: 0
                bottomPadding: 0
                awesomeIcon.text: "\uf2ed"
                awesomeIcon.size: 8
                font.pointSize: 8
                anchors.verticalCenter: parent.verticalCenter

                onClicked: {
                    __this__.remove(__name__.text);
                }
            }
        }
    }

    /*
     * Button to add
     */
    Button {
        id: __add__

        awesomeIcon.text: "\uf055"
        anchors.horizontalCenter: parent.horizontalCenter
        awesomeIcon.size: 30
        height: 40
        width: 40
        awesomeIcon.color: "#ffffff"
        background: Rectangle {
            color: "transparent"
        }

        Component.onCompleted: {
            console.log("Attributes button: Dim(", width, "x", height, ")");
        }

        onClicked: {
            __this__.add();
        }
    }
}
