import QtQuick 2.9
import QtQuick.Layouts 1.3
import "../Forms"

ColorPickerForm {
    button.onClicked: colorDialogRef.open()
}
