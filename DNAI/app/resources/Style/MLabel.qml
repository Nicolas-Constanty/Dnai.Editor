import QtQuick 2.0
import QtQuick.Controls 2.2

import DNAI 1.0

Label {
    color: AppSettings.theme["text"]["color"]
    font.family: AppSettings.theme["font"]["family"]
    font.pointSize: 10
    verticalAlignment: Text.AlignVCenter
    horizontalAlignment: Text.AlignHCenter
    renderType: Text.NativeRendering
    clip: true
}
