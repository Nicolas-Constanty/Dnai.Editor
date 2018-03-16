import QtQuick 2.0
import QtQuick.Controls 2.2

import DNAI 1.0

import "../Style"
import "../Components"
import "../Panels"

Rectangle {
    anchors.fill: parent
    color: "#16000000"
    property Modal openModal: null
    property Modal newModal: null

    Column {
        anchors.centerIn: parent
        spacing: 15
        LinkButton {
            text: qsTr("Create new project")
            mousearea.onPressed: {
                if (openModal !== null)
                    newProjectPopup.open()
            }
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Text {
            text: qsTr("or")
            color: "white"
            anchors.horizontalCenter: parent.horizontalCenter
        }
        LinkButton {
            text: qsTr("Open a project")
            mousearea.onPressed: {
                if (openModal !== null)
                    openProjectPopup.open()
            }
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
