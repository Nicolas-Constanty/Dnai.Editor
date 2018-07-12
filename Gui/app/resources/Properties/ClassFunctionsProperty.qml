import QtQuick 2.0
import QtQuick.Controls 2.2

import Dnai.Theme 1.0

BaseProperty {
    id: __this__

    property int functionHeight: 30

    signal setFunctionStatus(string name, bool member);

    anchors.left: parent.left
    anchors.right: parent.right

    height: header.height + 100

    ListView {
        id: __functions__

        model: __this__.model ? __this__.model.guiProperties.functions : []

        anchors.left: parent.left
        anchors.right: parent.right
        height: model.length * __this__.functionHeight

        delegate: Row {

            width: parent.width
            height: __this__.functionHeight

            Label {
                id: __name__

                width: parent.width * 0.5
                height: parent.height

                text: modelData
            }

            ComboBox {
                id: __status__

                width: parent.width * 0.5
                height: parent.height

                function isFuncMember()
                {
                    return __this__.model.guiProperties.isFunctionMember(__name__.text);
                }

                function getFuncIndex()
                {
                    return isFuncMember() ? 1 : 0;
                }

                model: ["Static", "Member"]
                currentIndex: getFuncIndex()

                onCurrentIndexChanged: {
                    if (getFuncIndex() === currentIndex)
                    {
                        return;
                    }

                    __this__.setFunctionStatus(__name__.text, currentIndex == 1);
                }
            }
        }
    }
}
