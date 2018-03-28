import QtQuick 2.0
import QtQuick.Controls 2.2

import DNAI 1.0

import "../Forms";

LoginForm {
    property Popup popup

    forgetPasswordLink.onClicked: {
        // TODO put link
        Qt.openUrlExternally("http://google.com")
    }

    createAccount.onClicked: {
        // TODO put link
        Qt.openUrlExternally("http://google.com")
    }

    signin.onClicked: {
        error = ""
        if (username.text && password.text) {
            Editor.session.signin(username.text, password.text);
        }
        username.text = ""
        password.text = ""
    }

    Connections {
        target: Editor.session

        onApiErrors: {
            error = "Invalid Credentials"
        }
    }
//    Rectangle {
//        anchors.fill: parent
//        opacity: 0.8
//        z: 99
//        radius: 10
//        color: AppSettings.style.background
//        BusyIndicator {
//            z: 100
//            anchors.centerIn: parent
//        }
//    }
}
