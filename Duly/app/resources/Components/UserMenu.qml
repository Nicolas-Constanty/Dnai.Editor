import QtQuick 2.4
import QtQuick.Controls 2.2
import Utils 1.0

import "../Forms"
import "../Panels"
import "../Components"

UserMenuForm {
    id: root
    fullname: ""
    imgSrc: ""
    opened: false


    mouseArea.onClicked: {
        if (!Manager.user) {
            loginPopup.open()
        } else {
            opened = !opened
            menu.open()
        }
    }

    logoutBtn.onClicked: {
        Manager.logout()
        root.fullname = ""
        root.imgSrc = ""
    }

    Connections {
        target: Manager

        onUserChanged: {
            loginPopup.close()
            root.fullname = Manager.user.name
            root.imgSrc = Manager.user.profile_url
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
}
