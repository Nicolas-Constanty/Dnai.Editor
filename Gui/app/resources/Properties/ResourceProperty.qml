import QtQuick 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.2

import Dnai.Controls 1.0
import Dnai.Theme 1.0

import DNAI.Core 1.0

BaseProperty {
    id: _panel
    property alias value: _value.text
    property alias label: _label.text
    name: "Resource property"
    property real contentHeight: 25

    anchors.left: parent.left
    anchors.right: parent.right
    height: _panel.contentHeight + header.height + _panel.content.anchors.topMargin * 2

    header.title.text: name
    Item {
        id: _property
        height: _panel.contentHeight
        anchors.left: parent.left
        anchors.right: parent.right

        Label {
            id: _label
            anchors.left: parent.left
            height: _panel.contentHeight
            text: "Select a file: "
            color: "white"
        }

        Item {
            id: _valueContainer

            anchors.left: _label.right
            anchors.right: parent.right
            height: _panel.contentHeight

            Text {
                id: _value

                anchors.left: parent.left
                anchors.right: _browseButton.left
                anchors.leftMargin: 20
                anchors.rightMargin: 10
                height: _panel.contentHeight

                font.pointSize: 12

                text: "--Empty--"
                color: "white"
                elide: Text.ElideRight
            }

            FileDialog {
                id: _browser
                title: "Select a file"
                selectExisting: true
                selectFolder: false
                selectMultiple: false
                nameFilters: ["Keras files (*.json *.h5)"]

                onAccepted: {
                    /*
                     * Copy du fichier dans le dossier de projet
                     */

                    var resourcePath = Controller.Resource.copyResource(_browser.fileUrl);

                    if (_panel.value)
                    {
                        var todelete = _panel.value.slice(1, _panel.value.length - 1)

                        console.log("Deleting old value", todelete)
                        Controller.Resource.deleteResource(todelete);
                    }

                    _panel.value = '"' + resourcePath + '"'
                    _panel.method(_panel.model, _panel.prop, _panel.value)
                    console.log("Value set to", _panel.value)
                }
            }

            Button {
                id: _browseButton

                height: _panel.contentHeight
                width: 100
                anchors.right: parent.right

                text: "Browse"

                onClicked: {
                    _browser.open()
                }
            }
        }
    }
}
