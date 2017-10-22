import QtQuick 2.4
import QtQuick.Controls 2.2

import Tools 1.0
import "../Forms"

OpenProjectForm {
    property Popup popup

    fileDialog.onAccepted: {
        console.log("You chose: " + fileDialog.fileUrl)
    }
    fileDialog.onRejected: {
        console.log("Canceled")
    }
    chooseButton.onClicked: fileDialog.open()
    openButton.onClicked: function () {
        if (projectPath.text) {
            Manager.loadProject(projectPath.text);
            popup.close()
        }
    }
}
