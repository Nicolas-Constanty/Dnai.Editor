import QtQuick 2.0
import QtQuick.Controls 2.2

import DNAI 1.0
import DNAI.Views 1.0

import "../Style"
import "../Components"
import "../Layouts"
import "../Panels"
import "../JavaScript/CreateComponent.js" as Factory

ApplicationWindow {
    id: _root
    Component.onCompleted: {
        Editor.checkVersion()
    }

    property alias appWindow: _root
//    property alias layout: _layout
    width: AppSettings.isSettingsLoad() ? 1280 : 400
    height: AppSettings.isSettingsLoad() ? 720 : 150
    minimumHeight: 150
    minimumWidth: 400
    title: qsTr("DNAI")
    color: AppSettings.style.background.darkColor
    visible: true

    ToolBarHeader {
        id: _toolBar
        height: 40
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
    }

    EditorView {
        id: _content
        anchors.top: _toolBar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        content: ViewZone {
            id: vz
            anchors.fill: parent
            TabView {
                id: tabV
                anchors.fill: parent
                Component.onCompleted: {
                    addView("resources/Views/DefaultView.qml",
                            {
                                "openModal" : openProjectPopup,
                                "newModal" : newProjectPopup
                            },
                            "Welcome")
                }
            }
        }
    }

    Modal {
        id: newProjectPopup
        x: parent.width / 2 - width / 2
        y: appWindow.height / 2 - height / 2
        background: Rectangle {
            color: AppSettings.style.background.color
        }
        width: 640
        height: 480
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
        contentItem: NewProject {
            anchors.fill: parent
            id: newFileProjectPanel
            popup: newProjectPopup
        }
    }
    Modal {
        id: openProjectPopup
        x: parent.width / 2 - width / 2
        y: _root.height / 2 - height / 2
        width: 700
        contentItem: OpenProject {
            anchors.fill: parent
            id: openProjectPanel
            popup: openProjectPopup

            openButton.onClicked: function () {
                if (projectPath.text) {
                    Editor.openSolution()
                    viewData.clear();
                    projectPath.text = "";
                    tabV.destroy()
                    _content.content.destroy()
                    Factory.createObjects("resources/Views/SolutionView.qml",
                                          {
                                              "openModal" : openProjectPopup,
                                              "newModal" : newProjectPopup
                                          }, _content)
                    _content.content = Factory.getObject()
                    popup.close();
                }
            }
        }
    }
}
