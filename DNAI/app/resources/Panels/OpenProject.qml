import QtQuick 2.4
import QtQuick.Controls 2.2
import DNAI 1.0

import "../Forms"
import "../Style"

OpenProjectForm {
    property Popup popup
    property Component onlineFilesDelegate: onlineFilesDelegate
    property int currentIndex: -1

//    popup.onOpened: function() {
//        Manager.session.updateCurentUserFiles();
//    }

    Connections {
        target: Manager

        onUserChanged: {
            isConnected = true;
            filesData.clear();
            for (var i = 0; i < Manager.user.files.length; ++i) {
                filesData.append(Manager.user.files[i]);
            }

            if (currentIndex != -1) {
                console.log(Manager.user.currentFileData);
                fillInformations(Manager.user.currentFileData);
            }
        }
    }

    fileDialog.folder: Qt.resolvedUrl(StandardPath.writableLocation((StandardPath.HomeLocation)))
    fileDialog.onAccepted: {
        projectPath.text = fileDialog.fileUrl;
        console.log("You chose: " + fileDialog.fileUrl);
        var data = Manager.session.loadProjectData(fileDialog.fileUrl);
        fillInformations(data);
    }

    function fillInformations(data) {
        viewData.clear();
        try {
            viewData.append({"field": "Nom", "value": data.name});
            viewData.append({"field": "Description", "value": data.description});
            viewData.append({"field": "Nombre de contexts", "value": data.count.contexts.toString()});
            viewData.append({"field": "Nombre de classes", "value": data.count.classes.toString()});
            viewData.append({"field": "Nombre de nodes", "value": data.count.nodes.toString()});
            viewData.append({"field": "Nombre de functions", "value": data.count.functions.toString()});
            viewData.append({"field": "Nombre de variables", "value": data.count.variables.toString()});
            viewData.append({"field": "Nombre de inputs", "value": data.count.inputs.toString()});
            viewData.append({"field": "Nombre de outputs", "value": data.count.outputs.toString()});
            viewData.append({"field": "Nombre de flows", "value": data.count.flows.toString()});
        } catch (e) {
            console.error(e);
            viewData.clear();
        }
    }

    fileDialog.onRejected: {
        console.log("Canceled")
    }
    chooseButton.onClicked: {
        fileDialog.open()
    }
    openButton.onClicked: function () {
        if (projectPath.text) {
            Manager.openProject(projectPath.text);
            viewData.clear();
            projectPath.text = "";
            popup.close();
        }
    }
    cancelButton.onClicked: function () {
        viewData.clear();
        projectPath.text = "";
        popup.close();
    }

    Component {
        id: onlineFilesDelegate
        Item {
            width: parent.width
            height: _downloadButton.height
            MLabel {
                anchors.left: parent.left
                anchors.right: _downloadButton.left
                height: _downloadButton.height
                text: title
                horizontalAlignment: Qt.AlignLeft
            }
            Button {
                id: _downloadButton
                text: "Use it"
                anchors.right: parent.right
                onClicked: {
                    currentIndex = index;
                    const filename = file.replace(/^.*[\\\/]/, '');
                    Manager.downloadProjectData(index, filename);
                }
            }
        }
    }
}
