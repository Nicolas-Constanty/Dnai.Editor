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
    property alias openProjectPopup: openProjectPopup
    property alias newProjectPopup: newProjectPopup
    Component.onCompleted: {
        Editor.checkVersion()
    }

    function openSolution (projectPath, viewData) {
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
        }
    }

    property alias appWindow: _root
//    property alias layout: _layout
    width: AppSettings.isSettingsLoad() ? 1280 : 400
    height: AppSettings.isSettingsLoad() ? 720 : 150
    minimumHeight: 150
    minimumWidth: 400
    title: qsTr("DNAI")
    color: AppSettings.theme["background"]["darkColor"]
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
    //    background: Rectangle {
    //        color: AppSettings.theme["background"]["color"]
    //    }
        width: newFileProjectPanel.widthValue
        height: newFileProjectPanel.heightValue
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
        contentItem: NewProject {
            anchors.fill: parent
            id: newFileProjectPanel
            popup: newProjectPopup

            onProjectCreated: function (projectName, path, solutionName) {
                if (path) {
                    Editor.openSolution()
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
    Modal {
        id: openProjectPopup
        x: parent.width / 2 - width / 2
        y: _root.height / 2 - height / 2
        width: 700
        contentItem: OpenProject {
            anchors.fill: parent
            id: openProjectPanel
            popup: openProjectPopup

            openButton.onClicked:
            {
                openSolution(projectPath, viewData)
                popup.close();
            }
        }
    }
}
