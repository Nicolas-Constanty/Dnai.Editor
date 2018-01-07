import QtQuick 2.4
import QtQuick.Controls 2.2

import "../Forms"

UploadForm {
    property Popup popup

    chooseButton.onClicked: fileDialog.open()
    fileDialog.onAccepted: {
        filesModel.clear();
        for (var i = 0; i < fileDialog.fileUrls.length; ++i) {
            const path = fileDialog.fileUrls[i];
            const filename = path.replace(/^.*[\\\/]/, '');
            filesModel.append({"filename": filename, "path": path});
        }
    }
}
