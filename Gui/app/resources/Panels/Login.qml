import QtQuick 2.2
import QtQuick.Controls 2.2
import QtQuick.Controls 1.0 as C
import QtQuick.Controls.Styles 1.0

import DNAI 1.0
import Dnai.Settings 1.0
import Dnai.FontAwesome 1.0

import "../Style"
import "../Forms";
import "../Components"

Item {
    id: loginViewId
    property Modal popup
    property int popupWidth: 350
    property int popupHeight: inputField.childrenRect.height + 40
    property string urlForgotPassword: "https://dnai.io/users/forgot-your-password/"
    property string urlCreateAccount: "https://dnai.io/users/register/"
    height: popupHeight
    width: popupWidth

    Connections {
        target: popup
        onClosed: {
            reset()
        }

        onOpened: {

        }
    }

    function reset() {
        usernameEditableId.focus = false
        passwordEditableId.focus = false
        usernameEditableId.text = ""
        passwordEditableId.text = ""
    }

    MouseArea {
        anchors.fill: parent
        onPressed: {
            usernameEditableId.focus = false
            passwordEditableId.focus = false
        }
    }

    TextAwesomeSolid {
        id: crossId
        text: "\uf00d"
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.topMargin: 10
        anchors.rightMargin: 10
        color: AppSettings.theme["text"]["color"]

        MouseArea {
            id: crossMouseId
            anchors.fill: crossId
            hoverEnabled: true
            //focus: true
            onEntered: {
                crossMouseId.cursorShape = Qt.PointingHandCursor
            }

            onReleased: {
                loginViewId.popup.close()
            }

            onExited: {
                crossMouseId.cursorShape = Qt.PointingHandCursor
            }
        }
    }

    Item {
        id: inputField
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.leftMargin: 40
        anchors.rightMargin: 40

        MLabel {
            id: loginLabelId
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Login"
            color: AppSettings.theme["text"]["color"]
            font.pointSize: 14
        }




    MLabel {
        id: usernameId
        anchors.top: loginLabelId.top
        anchors.left: inputField.left
        anchors.leftMargin: 20
        anchors.topMargin: 60
        font.pointSize: 12
        text: "Username or Email :"
        color: AppSettings.theme["text"]["color"]
    }

    EditableText {
        id: usernameEditableId
        anchors.top: usernameId.bottom
        anchors.left: inputField.left
        anchors.right: inputField.right
        height: 40
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        anchors.topMargin: 5
        horizontalAlignment: TextInput.AlignLeft
        placeholderText: ""
        KeyNavigation.tab: passwordEditableId
    }

    MLabel {
        id: passwordId
        anchors.top: usernameEditableId.bottom
        anchors.left: usernameId.left
        anchors.topMargin: 60
        font.pointSize: 12
        text: "Password :"
        color: AppSettings.theme["text"]["color"]
    }

    EditableText {
        id: passwordEditableId
        anchors.top: passwordId.bottom
        anchors.left: inputField.left
        anchors.right: inputField.right
        height: 40
        passwordCharacter: "*"
        echoMode: TextInput.Password
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        anchors.topMargin: 5
        horizontalAlignment: TextInput.AlignLeft
        placeholderText: ""
        KeyNavigation.tab: usernameEditableId
    }

    C.CheckBox {
        id: checkboxRememberId
        anchors.top: passwordEditableId.bottom
        anchors.left: inputField.left
        anchors.leftMargin: 20
        anchors.topMargin: 20
        anchors.right: loginButtonId.right
        style: CheckBoxStyle {

        label: Text {
            color: AppSettings.theme["text"]["color"]
            text: "Remember me"
        }

    }
        onCheckedChanged: {
            console.log(checkboxRememberId.checked)
            Editor.session.rememberUser = checkboxRememberId.checked
        }
    }

    MLabel {
        id: errorId
        text: ""
        color: AppSettings.theme["text"]["errorColor"]
        font.pointSize: 8
        anchors.top: checkboxRememberId.bottom
        anchors.left: inputField.left
        anchors.right: inputField.right
        anchors.rightMargin: 20
        anchors.leftMargin: 20
        anchors.topMargin: 30
    }

    CustomMenuButton {
        id: loginButtonId
        anchors.top: errorId.bottom
        anchors.left: inputField.left
        anchors.right: inputField.right
        anchors.rightMargin: 20
        anchors.leftMargin: 20
        height: 37
        textValue: "Sign In"

        onPressed: {
            if (usernameEditableId.text && passwordEditableId.text) {
                errorId.text = ""
                Editor.session.signin(usernameEditableId.text, passwordEditableId.text);
            } else {
                errorId.text = "Fields empty."
            }
        }
    }

    MTextClickable {
        id: createAccountId
        anchors.top: loginButtonId.bottom
        anchors.horizontalCenter: inputField.horizontalCenter
        anchors.topMargin: 20
        text: "You don't have an account yet ?"

        onPressed: {
            Qt.openUrlExternally(urlCreateAccount)
        }
    }

    MTextClickable {
        id: forgotPasswordId
        anchors.top: createAccountId.bottom
        anchors.horizontalCenter: createAccountId.horizontalCenter
        anchors.topMargin: 20
      //  anchors.bottom: inputField.bottom
        text: "Forgot password ?"

        onPressed: {
            Qt.openUrlExternally(urlForgotPassword)
        }
    }

    }

    Connections {
        target: Editor.session

        onApiErrors: {
            errorId.text = "Wrong password or username."
            console.log( "Invalid Credentials")
        }

        onUserChanged: {
            reset()
        }
    }








/*
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
//        username.text = ""
        password.text = ""
    }

    Connections {
        target: Editor.session

        onApiErrors: {
            error = "Invalid Credentials"
        }
    }*/
}
