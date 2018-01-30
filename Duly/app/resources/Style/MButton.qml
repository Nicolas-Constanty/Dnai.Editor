import QtQuick 2.0
import QtQuick.Controls 2.2

import Utils 1.0

Button {
    id: control
    contentItem: MLabel {
        id: _label
        text: control.text
    }
}
