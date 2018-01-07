import QtQuick 2.0
import QtQuick.Controls 2.2

import "../Forms";

LoginForm {
    property Popup popup

    forgetPasswordLink.onClicked: {
        Qt.openUrlExternally("http://google.com")
    }

    createAccount.onClicked: {
        Qt.openUrlExternally("http://google.com")
    }
}
