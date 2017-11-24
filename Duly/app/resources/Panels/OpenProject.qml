import QtQuick 2.4
import QtQuick.Controls 2.2
import Utils 1.0

import "../Forms"

OpenProjectForm {
    property Popup popup

    fileDialog.onAccepted: {
        console.log("You chose: " + fileDialog.fileUrl)
        var data = Manager.loadProjectData(fileDialog.fileUrl);
        viewData.clear();
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
    }
    fileDialog.onRejected: {
        console.log("Canceled")
    }
    chooseButton.onClicked: fileDialog.open()
    openButton.onClicked: function () {
        if (projectPath.text) {
            Manager.openProject(projectPath.text);
            popup.close()
            projectPath.text = "";
        }
    }
    cancelButton.onClicked: function () {
        popup.close()
        projectPath.text = "";
    }
}
