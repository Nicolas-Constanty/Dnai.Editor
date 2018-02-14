import QtQuick 2.9
import QtQuick.Controls 2.2
import DNAI 1.0

import "../Style"

MenuItem {
    id: control

    property string iconpath: ""

    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                            contentItem.implicitWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(background ? background.implicitHeight : 0,
                             Math.max(contentItem.implicitHeight,
                                      indicator ? indicator.implicitHeight : 0) + topPadding + bottomPadding)
    baselineOffset: contentItem.y + contentItem.baselineOffset

    padding: 6

    contentItem: Item {
        Row {
            anchors.verticalCenter: parent.verticalCenter
            spacing: 4
            Image {
                source: control.iconpath
                verticalAlignment: Text.AlignVCenter
                height: txt.implicitHeight
                width: txt.implicitHeight
                anchors.leftMargin: 4
            }
            MLabel {
                id: txt
                leftPadding: control.checkable && !control.mirrored ? control.indicator.width + control.spacing : 0
                rightPadding: control.checkable && control.mirrored ? control.indicator.width + control.spacing : 0

                text: control.text
                color: control.enabled ? DulySettings.style.text.lightColor : DulySettings.style.text.disableColor
                elide: Text.ElideRight
                visible: control.text
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
            }
        }
    }


    indicator: Image {
        x: control.mirrored ? control.width - width - control.rightPadding : control.leftPadding
        y: control.topPadding + (control.availableHeight - height) / 2

        visible: control.checked
        source: control.checkable ? "qrc:/qt-project.org/imports/QtQuick/Controls.2/images/check.png" : ""
    }

    background: Item {
        implicitWidth: 200
        implicitHeight: txt.implicitHeight * 1.4
        Rectangle {
            x: 1
            y: 1
            width: parent.width - 2
            height: parent.height - 2
            color: control.pressed ? DulySettings.style.background.darkColor : control.hovered ? DulySettings.style.background.lightColor : "transparent"
        }
    }
}
