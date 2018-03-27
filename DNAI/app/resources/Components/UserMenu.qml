import QtQuick 2.4
import QtQuick.Controls 2.2
import DNAI 1.0

import "../Forms"
import "../Panels"
import "../Components"

UserMenuForm {
    id: root
    fullname: ""
    imgSrc: ""
    opened: false

    Component.onCompleted: {
        Editor.app().session.getCurrentUser();
    }

    mouseArea.onClicked: {
        if (!Editor.app().session.user) {
            loginPopup.open()
        } else {
            opened = !opened
            menu.open()
        }
    }

    logoutBtn.onClicked: {
        Editor.app().session.logout()
        root.fullname = ""
        root.imgSrc = ""
    }

    uploadBtn.onClicked: {
        uploadPopup.open()
    }

    Connections {
        target: Editor.app().session

        onUserChanged: {
            loginPopup.close()
            if (!Editor.app().session.user) {
                return;
            }

            root.fullname = Editor.app().session.user.name
            root.imgSrc = Editor.app().session.user.profile_url
        }
    }

    Modal {
        id: loginPopup
        rootX: -root.x
        rootY: -root.y
        contentItem: Login {
            anchors.fill: parent
            popup: loginPopup
        }
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
}
