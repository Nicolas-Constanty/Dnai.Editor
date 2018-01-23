import QtQuick 2.0
import QtQuick.Controls 2.2

import Utils 1.0

Label {
    color: DulySettings.style.text.color
    font.family: DulySettings.style.font.family
    font.pointSize: 10
    verticalAlignment: Text.AlignVCenter
    horizontalAlignment: Text.AlignHCenter
    renderType: Text.NativeRendering
}
