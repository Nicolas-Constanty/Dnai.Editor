import QtQuick 2.4
import QtQuick.Controls 2.2

import DNAI 1.0

import "../Forms"

UploadForm {
    property Popup popup

    fileDialog.folder: Qt.resolvedUrl(StandardPath.writableLocation(StandardPath.HomeLocation))
    chooseBtn.onClicked: fileDialog.open()
    fileDialog.onAccepted: {
        filesModel.clear();
        for (var i = 0; i < fileDialog.fileUrls.length; ++i) {
            const path = fileDialog.fileUrls[i];
            const filename = path.replace(/^.*[\\\/]/, '');
            filesModel.append({"filename": filename, "path": path});
        }
    }
    uploadBtn.onClicked: {
        for (var i = 0; i < fileDialog.fileUrls.length; ++i) {
            Editor.session.uploadFile(fileDialog.fileUrls[i]);
        }
        popup.close()
    }
}
