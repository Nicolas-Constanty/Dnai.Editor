import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import Qt.labs.settings 1.0
import "../Forms"

ThemePanelForm {
    colRef.width: Math.max(implicitWidth, rectRef.availableWidth) - 20
}
