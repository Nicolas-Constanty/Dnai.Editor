import QtQuick 2.4
import QtQuick.Controls 2.2
import DNAI 1.0

import "../Forms"
import "../Panels"
import "../Components"
import "../Style"

UserMenuForm {
    id: root
    fullname: ""
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
}
