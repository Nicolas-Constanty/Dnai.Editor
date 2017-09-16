import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import Qt.labs.settings 1.0


ThemePanelForm {
    colRef.width: Math.max(implicitWidth, rectRef.availableWidth) - 20
}
//BasePanel {
//    content: ThemePanelForm {
//        ColumnLayout {
//            Rectangle {
//                        height: 40
//                        anchors.right: parent.right
//                        anchors.rightMargin: 0
//                        anchors.left: parent.left
//                        anchors.leftMargin: 0
//                        color: "transparent"
//                        Layout.fillWidth: false
//                        id: colorPickerForm
//                        RowLayout {
//                            anchors.verticalCenter: parent.verticalCenter
//                            anchors.left: parent.left
//                            anchors.leftMargin: 0
//                            anchors.right: parent.right
//                            anchors.rightMargin: 0
//                            Label {
//                                id: label
//                                text: qsTr("Label")
//                                anchors.left: parent.left
//                                anchors.leftMargin: 0
//                                anchors.verticalCenter: parent.verticalCenter
//                            }
//                            ComboBox {
//                                id: comboBox
//                                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
//                                textRole: qsTr("")
//                                currentIndex: 0

//                                model: ListModel {
//                                    id: listModel
//                                    ListElement {
//                                        text: "Dark"
//                                    }
//                                    ListElement {
//                                        text: "Light"
//                                    }
//                                }
//                            }
//                        }
//                    }
//            ListView {
//                interactive: false
//    //            anchors.rightMargin: 20
//    //            anchors.leftMargin: 20
//    //            anchors.bottomMargin: 20
//    //            anchors.topMargin: 50
//                anchors.fill: parent
//                model: ColorPickerModel {
//                }
//                delegate: contactsDelegate
//                Component {
//                    id: contactsDelegate
//                    ColorPicker {
//                        name: label
//                        anchors.right: parent.right
//                        anchors.rightMargin: 0
//                        anchors.left: parent.left
//                        anchors.leftMargin: 0
//                        height: 50
//                    }
//                }
//        }


//        }
//    }
//}
