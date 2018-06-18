import QtQuick 2.0
import QtQuick.Controls 2.2

import "../Style"

BaseProperty {
    id: __this__

    property int functionHeight: 30

    signal setFunctionStatus(string name, bool member);

    anchors.left: parent.left
    anchors.right: parent.right

    height: header.height + 100

    ListView {
        id: __functions__

        model: [{"first": "toto", "second": true}, {"first": "tata", "second": false}, {"first": "hey", "second": false}, {"first": "titi", "second": true}]// __this__.model ? __this__.model.guiProperties.functions : []

        anchors.left: parent.left
        anchors.right: parent.right
        height: model.length * __this__.functionHeight

        delegate: Row {

            width: parent.width
            height: __this__.functionHeight

            MLabel {
                id: __name__

                width: parent.width * 0.5
                height: parent.height

                text: modelData.first
            }

            ComboBox {
                id: __status__

                width: parent.width * 0.5
                height: parent.height

                model: ["Static", "Member"]
                currentIndex: !modelData.second ? 0 : 1

                onCurrentIndexChanged: {
                    if ((modelData.second && currentIndex == 1)
                        || (!modelData.second && currentIndex == 0))
                        return;
                    __this__.setFunctionStatus(modelData.first, currentIndex == 1);
                }
            }
        }
    }
}
