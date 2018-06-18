import QtQuick 2.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.2

import DNAI 1.0
import Dnai.Settings 1.0
import Dnai.FontAwesome 1.0

import "../Forms"
import "../Panels"
import "../Components"
import "../Style"

Item {
    id: root
    /*fullname: ""
    imgSrc: ""
    opened: false

    Component.onCompleted: {
        Editor.session.getCurrentUser();
    }

    mouseArea.onClicked: {
        if (!Editor.session.user) {
            loginPopup.open()
        } else {
            opened = !opened
            menu.open()
        }
    }

    logoutBtn.onClicked: {
        Editor.session.logout()
        root.fullname = ""
        root.imgSrc = ""
    }

    uploadBtn.onClicked: {
        uploadPopup.open()
    }

    Connections {
        target: Editor.session

        onUserChanged: {
            loginPopup.close()
            if (!Editor.session.user) {
                return;
            }

            root.fullname = Editor.session.user.name
            root.imgSrc = Editor.session.user.profile_url
        }
    }*/

    Component.onCompleted: {
        Editor.session.getCurrentUser();
    }

    function onConnectionSuccess() {
        containerId.visible = true
        backgroundSelectionId.visible = false
        borderId.visible = false
        signInId.visible = false
    }

    function onLogoutSuccess() {
        containerId.visible = false
        backgroundSelectionId.visible = true
        borderId.visible = true
        signInId.visible = true
    }

    ColumnLayout {
        id: containerId
        visible: false
        spacing: 0
        anchors.top: parent.top
        anchors.topMargin: 3
        anchors.bottomMargin: 3
        anchors.bottom: parent.bottom
        anchors.right: backgroundProfileId.left
        anchors.rightMargin: 10

        MText {
            id: usernameId
            text: ""
            font.pointSize: 9
        }
        MTextClickable {
            id: logoutId
            text: "Sign out"
            font.pointSize: 8
            anchors.right: parent.right
            onPressed: {
                Editor.session.logout()
            }
        }
    }

    Rectangle {
        id: borderId
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: signInId.left
        anchors.rightMargin: 15
        width: 1
        color: AppSettings.theme["shadowColor"]
    }

    MText {
        id: signInId
        text: "Sign In"
        anchors.rightMargin: 15
        anchors.right: backgroundProfileId.left
        anchors.verticalCenter: backgroundProfileId.verticalCenter
        font.pointSize: 12
        color: AppSettings.theme["text"]["color"]
    }

    Rectangle {
        id: backgroundProfileId
        color: containerId.visible == false ? AppSettings.theme["colors"]["accent"]["blue"] : AppSettings.theme["colors"]["accent"]["green"]
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        width: profileImageId.width + (profileImageId.anchors.rightMargin * 2)

        Rectangle {
            width: profileImageId.width - 4
            height: width
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin: 7
            color: AppSettings.theme["colors"]["background"]["base"]
            radius: width / 2
        }
        TextAwesomeSolid {
            id: profileImageId
            text: "\uf2bd"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin: 7
            font.pointSize: 23
            color: containerId.visible == false ? AppSettings.theme["colors"]["accent"]["blue"] : AppSettings.theme["colors"]["accent"]["green"]
        }
    }

    Rectangle {
        id: backgroundSelectionId
        color: "transparent"
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: borderId.right
        anchors.right: parent.right

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            hoverEnabled: true
            onEntered: {
                backgroundSelectionId.color = "white"
                backgroundSelectionId.opacity = 0.1
            }

            onReleased: {
                loginPopup.open()
            }

            onExited: {
                backgroundSelectionId.color = "transparent"
                backgroundSelectionId.opacity = 1
            }

        }
    }

    Modal {
        id: loginPopup
        rootX: -root.x
        rootY: -root.y
        contentItem: Login {
            id: loginPopupItem
            anchors.fill: parent
            popup: loginPopup
        }
        width: loginPopupItem.popupWidth
        height: loginPopupItem.popupHeight
    }


    Modal {
        id: uploadPopup
        rootX: -root.x
        rootY: -root.y
        width: 500
        height: 100
        contentItem: Upload {
            anchors.fill: parent
            popup: uploadPopup
        }
    }

    Connections {
        target: Editor.session

        onUserChanged: {
            loginPopup.close()
            if (!Editor.session.user) {
                onLogoutSuccess()
                return;
            }
            usernameId.text = Editor.session.user.name
            onConnectionSuccess()

            // root.fullname = Editor.session.user.name
            // root.imgSrc = Editor.session.user.profile_url
        }
    }
}
