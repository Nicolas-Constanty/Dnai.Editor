import QtQuick 2.4
import QtQuick.Controls 2.2
import DNAI 1.0

import "../Forms"

NewProjectForm {
    property Popup popup

    fileDialog.folder: Qt.resolvedUrl(StandardPath.writableLocation((StandardPath.HomeLocation)))

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
    }
}
