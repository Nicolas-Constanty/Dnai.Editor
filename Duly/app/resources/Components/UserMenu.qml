import QtQuick 2.4

import "../Forms"

UserMenuForm {
    id: root
    connected: true
    fullname: "John Doe"
    imgSrc: "../Images/default_user.png"
    height: parent.height
    opened: false

    mouseArea.onClicked: {
        opened = !opened
        menu.open()
    }
}
