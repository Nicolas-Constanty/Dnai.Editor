import QtQuick 2.9
import QtQuick.Controls 2.2

import DNAI.Models 1.0
import "../Style"

Item {
    id: item
    property Entity entity: null
    property alias nameColumn: columnName
    property alias valueColumn: valueName

    ListModel {
        id: entityModel
        ListElement { text: qsTr("Namespace");  }
        ListElement { text: qsTr("Class");  }
        ListElement { text: qsTr("Function");  }
        ListElement { text: qsTr("Variable");  }
    }

    ListModel {
        id: classModel
        ListElement { text: qsTr("Class");  }
        ListElement { text: qsTr("Function");  }
        ListElement { text: qsTr("Variable");  }
        ListElement { text: qsTr("Method");  }
        ListElement { text: qsTr("Attribute");  }
    }

    Row {
        Column {
            id: columnName

            MText {
                id: name
                text: qsTr("Name")
            }
            MText {
                id: description
                text: qsTr("Description")
            }
            MText {
                id: type
                text: qsTr("Type")
            }
            MText {
                id: visibility
                text: qsTr("Visibility")
            }
        }

        Column {
            id: valueName
            EditableText {
                text: entity.name
            }
            EditableText {
                text: entity.description
            }
            ComboBox {
                id: typevalue
                anchors.right: parent.right
                textRole: qsTr("")
                currentIndex: 0
                model: (entity.type === 0) ? classModel : entityModel
            }

            ComboBox {
                id: visibilityvalue
                anchors.right: parent.right
                textRole: qsTr("")
                currentIndex: 0
                model: ListModel {
                    id: model
                    ListElement { text: qsTr("Public");  }
                    ListElement { text: qsTr("Private");  }
                }
            }
        }
    }
}
