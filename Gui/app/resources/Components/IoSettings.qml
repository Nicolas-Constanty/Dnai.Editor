import QtQuick 2.0
import QtQuick.Controls 2.2

import Dnai.Controls 1.0
import Dnai.FontAwesome 1.0
import Dnai.Settings 1.0
import DNAI.Core 1.0

Item {
    id: _inputItem
    property alias colorWheel: _controlWheel

    SwipeView {
        id: _swipeView
        interactive: false
        height: currentItem.height
        anchors.left: parent.left
        anchors.right: parent.right

        state: "Collapse"

        states: [
            State {
                name: "Collapse"
                PropertyChanges { target: _firstView; height: 40 }
                PropertyChanges { target: _inputItem; height: 40 }
            },
            State {
                name: "Expended"
                PropertyChanges { target: _inputItem; height: _secondView.trueHeight }
                PropertyChanges { target: _secondView; height: _secondView.trueHeight }
            }
        ]

        transitions: [
            Transition {
                from: "Collapse"
                to: "Expended"
                NumberAnimation {
                    target: _firstView
                    duration: 200
                    property: "height"
                    easing.type: Easing.InOutQuad
                }
                NumberAnimation {
                    target: _inputItem
                    duration: 200
                    property: "height"
                    easing.type: Easing.InOutQuad
                }
            },
            Transition {
                from: "Expended"
                to: "Collapse"
                NumberAnimation {
                    target: _inputItem
                    duration: 200
                    property: "height"
                    easing.type: Easing.InOutQuad
                }
                NumberAnimation {
                    target: _secondView
                    duration: 200
                    property: "height"
                    easing.type: Easing.InOutQuad
                }
            }
        ]

        onCurrentIndexChanged: {
            if (currentIndex == 0)
            {
                _swipeView.state = "Collapse"
            }
            else
            {
                _swipeView.state = "Expended"
            }
        }

        currentIndex: 0
        SettingsItem {
            id: _firstView
            height: 40
            width: _inputItem.width
            text: "Input color"
            content: Component {
                Row {
                    property alias seletctedType: _selectedType
                    spacing: 10
                    height: parent.height
                    Rectangle {
                        id: _outerColor
                        height: 30
                        width: 30
                        radius: 15
                        color: _outerColorDisplay.color
                        anchors.verticalCenter: parent.verticalCenter
                        MouseArea {
                            id: _colorSelection
                            anchors.fill: parent
                            onClicked: {
                                _swipeView.currentIndex = 1
                            }
                        }
                        Rectangle {
                            id: _innerColor
                            height: 20
                            width: 20
                            radius: 10
                            anchors.centerIn: parent
                            color: _innerColorDisplay.color
                        }
                    }
                    ComboBox {
                        id: _selectedType
                        property var types: Controller.types
                        property var completeType: null
                        model: completeType
                        onTypesChanged: {
                            completeType = types
                            completeType.push({"name": "Generic"})
                        }

                        textRole: "name"
                    }
                }
            }
        }
        Item {
            id: _secondView
            property real trueHeight: 150
            width: _inputItem.width

            ButtonAwesomeSolid {
                text: "\uf00d"
                height: 20
                width: 20
                color: AppSettings.theme["text"]["color"]
                anchors.right: parent.right
                anchors.top: parent.top
                background: Item {
                }
                onClicked: {
                    _swipeView.currentIndex = 0
                }
            }

            ColorWheel {
                id: _controlWheel
                radius: _secondView.trueHeight / 2
                onPointingColorChanged: {
                    if (_swicht.checked)
                    {
                        AppSettings.theme["types"][_firstView.contentItem.children[0].children[0].seletctedType.currentText]["inner"] = _controlWheel.pointingColor
                    }
                    else
                    {
                        AppSettings.theme["types"][_firstView.contentItem.children[0].children[0].seletctedType.currentText]["outer"] = _controlWheel.pointingColor
                    }
                }
            }
            Rectangle {
                anchors.centerIn: parent
                id: _outerColorDisplay
                height: 70
                width: height
                radius: width / 2
                color: AppSettings.theme["types"][_firstView.contentItem.children[0].children[0].seletctedType.currentText]["outer"]
                Rectangle {
                    id: _innerColorDisplay
                    height: _outerColorDisplay.height * 0.75
                    width: height
                    radius: width / 2
                    color: AppSettings.theme["types"][_firstView.contentItem.children[0].children[0].seletctedType.currentText]["inner"]
                    anchors.centerIn: parent
                }
            }

            Switch {
                id: _swicht
                anchors.right: parent.right
                text: _swicht.checked ? qsTr("Inner") : qsTr("Outer")
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }
}
