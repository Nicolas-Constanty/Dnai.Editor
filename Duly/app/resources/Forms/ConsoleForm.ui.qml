import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0
import DulyUtils 1.0

Item {
    id: defaultPanel

    property string title: "Title"
    property alias consoleRef: textArea
    property alias consoleListDelegate: textArea.delegate
    property alias heightInfoPanel: mainColumn.height
    property alias widthInfoPanel: mainColumn.width
    property alias heightItem: defaultPanel.height
    property alias consoleMode: comboBox
    property alias consoleRefMode: cons

    Rectangle {
        id: rectangle
        color: "#303030"
        anchors.fill: parent
        border.color: "#3f3f46"
        border.width: 1
        Material.theme: Material.Dark
        Material.accent: Material.color(Material.DeepOrange, Material.Shade400)
        Grid {
            columns: 0
            anchors.fill: parent

            Column {
                id: column
                width: parent.width
                height: parent.height

                Rectangle {
                    id: mainColumn
                    color: "transparent"

                    width: parent.width
                    height: childrenRect.height + firstRow.anchors.topMargin * 2
                    border.color: "#3f3f46"
                    border.width: 1

                    Row {
                        spacing: 10
                        id: firstRow
                        x: 5
                        y: 10
                        anchors.left: parent.left
                        anchors.leftMargin: firstRow.spacing / 2
                        anchors.top: parent.top
                        anchors.topMargin: 4
                        Rectangle {
                            id: firstColumn
                            width: labelName.width
                            height: parent.height

                            color: "transparent"
                            Label {
                                id: labelName
                                font.pixelSize: 12
                                text: defaultPanel.title
                                rightPadding: 10
                                textFormat: Text.PlainText
                                verticalAlignment: Text.AlignVCenter
                                bottomPadding: 0
                                topPadding: 0
                                renderType: Text.QtRendering
                                wrapMode: Text.NoWrap
                                anchors.centerIn: parent
                            }
                        }

                        Rectangle {
                            width: gridImage.width
                            height: parent.height
                            color: "transparent"
                            Image {
                                id: gridImage
                                width: rectangle.width - firstColumn.width
                                       - firstRow.spacing * 4 - comboBox.width
                                height: 16
                                sourceSize.height: 16
                                sourceSize.width: 16
                                fillMode: Image.TileHorizontally
                                source: "../Images/WindowHandle.png"
                                anchors.centerIn: parent
                            }
                        }

                        ComboBox {
                            id: comboBox
                            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                            textRole: qsTr("")
                            currentIndex: 0
                            model: ListModel {
                                id: listModel
                                ListElement {
                                    text: "Default"
                                }
                                ListElement {
                                    text: "Verbose"
                                }
                            }
                        }
                    }
                }
                Rectangle {
                    width: widthInfoPanel
                    height: heightItem - heightInfoPanel
                    color: "transparent"

                    Console {
                        id: cons
                    }
                    ListView {
                        id: textArea
                        anchors.rightMargin: 30
                        anchors.leftMargin: 30
                        anchors.bottomMargin: 10
                        anchors.topMargin: 30
                        anchors.fill: parent
                        model: cons.text
                    }
                }
            }
        }
    }
}
