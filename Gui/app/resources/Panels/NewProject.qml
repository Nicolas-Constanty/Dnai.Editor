import QtQuick 2.4
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.3

import DNAI 1.0
import Dnai.Settings 1.0
import Dnai.FontAwesome 1.0
import Dnai.Controls 1.0
import Dnai.Theme 1.0


import "../Forms"
import "../Components"
import "../Style"

Item {
    id: _newProj

    property Popup popup
    property int widthValue: 650
    property int heightValue: container.childrenRect.height + 40

    signal projectCreated(string project, string path, string solution)

    Connections {
        target: popup
        onClosed: {
            reset()
        }

        onOpened: {

        }
    }

    function reset() {
        locationEditable.errorText = ""
        nameEditable.errorText = ""
        solutionNameEditable.errorText = ""
        locationEditable.focus = false
        nameEditable.focus = false
        solutionNameEditable.focus = false
        locationEditable.text = ""
        nameEditable.text = ""
        solutionNameEditable.text = ""

    }

    FileDialog {
        id: fileDialog
        title: "Choose a directory"
        folder: Qt.resolvedUrl(StandardPath.writableLocation((StandardPath.HomeLocation)))
        selectFolder: true
        selectExisting: true
        onAccepted: {
            locationEditable.text = fileDialog.fileUrl
        }
    }

    MouseArea {
        anchors.fill: parent

        onPressed: {
            nameEditable.focus = false
            solutionNameEditable.focus = false
            locationEditable.focus = false
        }
    }

    function resetData() {
        nameEditable.focus = false
        solutionNameEditable.focus = false
        locationEditable.focus = false
        nameEditable.text = ""
        solutionNameEditable.text = ""
        locationEditable.text = ""
    }


    TextAwesomeSolid {
        id: crossId
        text: "\uf00d"
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.topMargin: 10
        anchors.rightMargin: 10
        color: AppSettings.theme["text"]["color"]

        MouseArea {
            id: crossMouseId
            anchors.fill: crossId
            hoverEnabled: true
            //focus: true
            onEntered: {
                crossMouseId.cursorShape = Qt.PointingHandCursor
            }

            onReleased: {
                popup.close()
            }

            onExited: {
                crossMouseId.cursorShape = Qt.PointingHandCursor
            }
        }
    }




    Item {
        id: container
        anchors.fill: parent
        anchors.margins: 40
        anchors.topMargin: 20



        Label {
            id: title
            text: "Create new project"
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: 14
        }

        Label {
            id: name
            text: "Name:"
            anchors.top: title.bottom
            anchors.topMargin: 20
            anchors.verticalCenter: nameEditable.verticalCenter
            font.pointSize: 12
        }

        TextField {
            id: nameEditable
            anchors.top: title.bottom
            anchors.topMargin: 20
            anchors.left: solutioName.right
            anchors.leftMargin: 10
            anchors.right: parent.right
            height: 30
            horizontalAlignment: TextInput.AlignLeft
            KeyNavigation.tab: solutionNameEditable
            placeholderText: "Project's name ..."
            onTextChanged: {
                solutionNameEditable.text = nameEditable.text
            }
        }

        Label {
            id: location
            text: "Location:"
            anchors.top: nameEditable.bottom
            anchors.topMargin: 20
            anchors.verticalCenter: locationEditable.verticalCenter
            font.pointSize: 12
        }

        TextField {
            id: locationEditable
            anchors.top: nameEditable.bottom
            anchors.topMargin: 20
            anchors.left: solutioName.right
            anchors.leftMargin: 10
            anchors.right: browseLocation.left
            anchors.rightMargin: 20
            height: 30
            horizontalAlignment: TextInput.AlignLeft
            KeyNavigation.tab: solutionNameEditable
            canEdit: false
            placeholderText: ""
        }

        CustomMenuButton {
            id: browseLocation
            anchors.right: parent.right
            anchors.top: locationEditable.top
            anchors.bottom: locationEditable.bottom
            width: browseLocation.textWidth + 20
            height: browseLocation.textHeight + 20
            textValue: "Browse..."
            textPointSize: 12

            onPressed: {
                fileDialog.open()
            }
        }

        Label {
            id: solutioName
            text: "Solution name:"
            anchors.top: locationEditable.bottom
            anchors.topMargin: 20
            anchors.verticalCenter: solutionNameEditable.verticalCenter
            font.pointSize: 12
        }

        TextField {
            id: solutionNameEditable
            anchors.top: locationEditable.bottom
            anchors.topMargin: 20
            anchors.left: solutioName.right
            anchors.leftMargin: 10
            anchors.right: parent.right
            height: 30
            horizontalAlignment: TextInput.AlignLeft
            KeyNavigation.tab: nameEditable
            placeholderText: "Project's solution name ..."
        }

        CustomMenuButton {
            id: validateButton
            anchors.top: solutionNameEditable.bottom
            anchors.topMargin: 20
            anchors.horizontalCenter: parent.horizontalCenter
            width: validateButton.textWidth + 20
            height: validateButton.textHeight + 20
            textValue: "Create Project"

            onPressed: {
                if (locationEditable.text && solutionNameEditable.text && nameEditable.text) {
                    if (Editor.createSolution(solutionNameEditable.text,
                                         "",
                                         locationEditable.text,
                                         nameEditable.text,
                                         ""))
                    {
                        _newProj.projectCreated(nameEditable.text, locationEditable.text, solutionNameEditable.text);
                        popup.close();
                        resetData();
                    }
                } else {
                    if (!locationEditable.text)
                        locationEditable.errorText = "Field is empty"
                    else {
                        locationEditable.errorText = ""
                    }

                    if (!nameEditable.text)
                        nameEditable.errorText = "Field is empty"
                    else {
                        nameEditable.errorText = ""
                    }

                    if (!solutionNameEditable.text)
                        solutionNameEditable.errorText = "Field is empty"
                    else {
                        solutionNameEditable.errorText = ""
                    }
                }
            }
        }

    }

    /*fileDialog.folder: Qt.resolvedUrl(StandardPath.writableLocation((StandardPath.HomeLocation)))

    fileDialog.onAccepted: {
        console.log("You chose: " + fileDialog.fileUrl)
    }
    fileDialog.onRejected: {
        console.log("Canceled")
    }
    chooseButton.onClicked: fileDialog.open()
    createButton.onClicked: function () {
        if (solutionPath.text && solutionName.text) {
            Editor.createSolution(solutionName.text,
                                 solutionDescription.text,
                                 solutionPath.text,
                                 projectName.text,
                                 projectDescription.text);
            popup.close()
            projectName.text = "";
            projectDescription.text = "";
        }
    }
    cancelButton.onClicked: function () {
        popup.close()
        projectName.text = "";
        projectDescription.text = "";
        projectPath.text = "";
    }*/
}
