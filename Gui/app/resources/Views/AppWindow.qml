import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.3

import DNAI 1.0
import DNAI.Views 1.0
import Dnai.Settings 1.0

import "../Style"
import "../Components"
import "../Panels"
import "../JavaScript/Utils.js" as Utils
import "../JavaScript/CreateComponent.js" as Factory

ApplicationWindow {
    id: _root
    property alias openProjectId: openProjectId
    property alias newProjectPopup: newProjectPopup
    Component.onCompleted: {
        console.log("Hello")
        Editor.checkVersion()
    }



    function openSolution (projectPath) {
        if (Editor.loaded)
        {
            Editor.newEditor(projectPath);
        }
        else
        {
            Editor.loadSolution(projectPath);
            Editor.openSolution()
            tabV.destroy()
            _content.content.destroy()
            Factory.createObjects("resources/Views/SolutionView.qml",
                                  {
                                      "openModal" : openProjectId,
                                      "newModal" : newProjectPopup
                                  }, _content)
            _content.content = Factory.getObject()
        }
    }

    property alias appWindow: _root

    width: AppSettings.isSettingsLoad() ? 1280 : 400
    height: AppSettings.isSettingsLoad() ? 720 : 150
    minimumHeight: 150
    minimumWidth: 400
    title: qsTr("DNAI")
    color: AppSettings.theme["colors"]["background"]["dark"]
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
                                "openModal" : openProjectId,
                                "newModal" : newProjectPopup
                            },
                            qsTr("Welcome"))
                    if (Editor.solutionName) {
                        openSolution(Editor.solutionName); //load fails
                    }
                }
            }
        }
    }

    Modal {
        id: newProjectPopup
        x: parent.width / 2 - width / 2
        y: appWindow.height / 2 - height / 2

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
                    openSolution(path + "/" + solutionName + ".dnaisolution");
                    popup.close();
                }
            }
        }
    }

    FileDialog {
        id: openProjectId
        title: "Choose a Project name"
        folder: Qt.resolvedUrl(StandardPath.writableLocation((StandardPath.HomeLocation)))
        nameFilters: [ "DNAI Solution files (*.dnaisolution)" ]

        onAccepted: {
            openSolution(openProjectId.fileUrl);
        }
    }

    Modal {
        id: dialogPopup
        x: _root.width / 2 - dialogPopupItem.width / 2
        y: _root.height / 2 - dialogPopupItem.height / 2
        contentItem: DialogPopup {
            id: dialogPopupItem
            anchors.fill: parent
            popup: dialogPopup
            title: "Warning"
            description: "Do you want to save before leaving ?"
            icon: "\uf071"
            iconColor: AppSettings.theme["colors"]["accent"]["yellow"]

            buttonModel: [{
              "text": "No",
              "hoverColor": AppSettings.theme["colors"]["background"]["color5"],
              "notHoverColor": AppSettings.theme["colors"]["background"]["color5"],
              "colorRect": AppSettings.theme["colors"]["background"]["base"],
              "hoverColorRect": AppSettings.theme["colors"]["background"]["light"],
              "onPressedAction": Utils.createCallBack(noAnswer)
            }, {
                    "text": "Yes",
                    "hoverColor": AppSettings.theme["button"]["text"]["hovercolor"],
                    "notHoverColor": AppSettings.theme["button"]["text"]["color"],
                    "colorRect": AppSettings.theme["button"]["color"],
                    "hoverColorRect": AppSettings.theme["button"]["hovercolor"],
                    "onPressedAction": Utils.createCallBack(yesAnswer)
                }

            ]

                function yesAnswer() {
                    Editor.solution.save()
                    dialogPopup.close()
                    Qt.quit()
                }


                function noAnswer() {
                    Qt.quit()
                }

        }
        width: dialogPopupItem.widthValue
        height: dialogPopupItem.heightValue
    }



    onClosing: {
        close.accepted = true
        if (Editor.solution && Editor.solution.isProjectsSaved() === false) {
            dialogPopup.open()
            close.accepted = false
        }
    }
}
