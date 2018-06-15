import QtQuick 2.0

import DNAI 1.0
import Dnai.Settings 1.0

Text {
    text: qsTr("Text")
    color: AppSettings.theme["text"]["color"]
    font.family: AppSettings.theme["font"]["family"]
    font.pointSize: 10
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
    clip: true
}
