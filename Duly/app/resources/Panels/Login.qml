import QtQuick 2.0
import QtQuick.Controls 2.2

import Utils 1.0

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
        if (username.text && password.text) {
            Manager.signin(username.text, password.text);
        }
        username.text = ""
        password.text = ""
    }
}
