import QtQuick 2.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import DNAI 1.0

ColumnLayout {
    property alias createAccount: createAccount
    property alias signin: signin
    property alias forgetPasswordLink: forgetPasswordLink
    property alias username: login
    property alias password: password
    property string error: ""

    anchors.fill: parent
    anchors.margins: 3
    spacing: 3

    Rectangle {
        id: header
        color: "#00000000"
        Layout.alignment: Qt.AlignLeft | Qt.AlignTop
        Layout.fillWidth: true
        Layout.preferredHeight: 100
        Text {
            text: "Login"
            font.bold: true
            font.pointSize: 50
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            color: AppSettings.style.text.color
        }
    }

    ColumnLayout {
        id: columnLayout
        Layout.preferredHeight: 300
        Layout.alignment: Qt.AlignLeft | Qt.AlignTop
        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.margins: 20
        Text {
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text: error
            color: "#F44336"
        }

        TextField {
            id: login
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            Layout.fillWidth: true
            placeholderText: qsTr("Username")
        }

        TextField {
            id: password
            Layout.fillWidth: true
            placeholderText: qsTr("Password")
            echoMode: TextInput.Password
        }

        Text {
            id: forgetPasswordText
            text: '<a href="http://google.com">' + qsTr("Forgot Password ?") + '</a>';
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            verticalAlignment: Text.AlignTop
            font.capitalization: Font.Capitalize
            font.weight: Font.Medium
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 12
            color: AppSettings.style.text.color
            linkColor: AppSettings.style.text.linkColor
            MouseArea {
                id: forgetPasswordLink
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
            }
        }

        Button {
            id: signin
            text: qsTr("Sign In")
            highlighted: false
            Layout.fillWidth: true
        }

        Text {
            id: noAccount
            text: qsTr("Don't have an account?")
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignTop
            font.capitalization: Font.Capitalize
            Layout.fillWidth: true
            font.weight: Font.Medium
            font.pixelSize: 12
            color: AppSettings.style.text.color
        }

        Text {
            id: createAccountText
            text: '<a href="http://google.com">' + qsTr("Click here to create one") + '</a>'
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignTop
            font.capitalization: Font.Capitalize
            font.weight: Font.Medium
            font.pixelSize: 12
            color: AppSettings.style.text.color
            linkColor: AppSettings.style.text.linkColor
            MouseArea {
                id: createAccount
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
            }
        }
    }
}
