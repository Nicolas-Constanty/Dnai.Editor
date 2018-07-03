import QtQuick 2.0

import DNAI.Views 1.0
import DNAI.Enums 1.0
import DNAI.Core 1.0

import Dnai.Settings 1.0

import "../Style"

GenericNode {
    id: __this__

    property var function_entity

    header: _content
    content: _content

    width: childrenRect.width
    height: childrenRect.height

    onXChanged: {
        function_entity.guiProperties.entryPointX = x;
    }

    onYChanged: {
        function_entity.guiProperties.entryPointY = y;
    }

    /*
     * Content
     */
    RoundedRectangle {
        id: _content

        x: borderWidth * 2
        y: borderWidth * 2

        width: _name.width + _flow.width + 50
        height: _name.height + 20

        radius: 10
        borderWidth: 1
        borderColor: "#7C7C7C"
        fillColor: "#aa700707"
        antialiasing: true
        topRight: false
        bottomLeft: false

        /*
         * Name
         */
        MLabel {
            id: _name

            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            anchors.margins: 10

            text:  "On called"
        }

        /*
         * Flow out
         */
        Flow {
            id: _flow

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                propagateComposedEvents: true
                onContainsMouseChanged: {
                    _flow.isHover = containsMouse
                }
                onPressed: {
                    mouse.accepted = false
                }
            }

            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.margins: 10

            curveColor: AppSettings.theme["flow"]["outer"]
            borderColor: isHover ? AppSettings.theme["flow"]["inner"] : AppSettings.theme["flow"]["outer"]
            fillColor: isLink || isHover ? AppSettings.theme["flow"]["outer"] : AppSettings.theme["flow"]["inner"]

            width: 17
            height: 17

            typeFlow: FlowType.Exit

            radius: 6
            borderWidth: 3
            antialiasing: true

            onLinked: {
                Controller.Function.setEntryPoint(__this__.function_entity.id, instructionModel.uid);
            }

            onUnlinked: {
                console.log("Unset entry point")
            }
        }
    }
}
