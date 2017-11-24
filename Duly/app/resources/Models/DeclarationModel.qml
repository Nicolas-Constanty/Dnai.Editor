import QtQuick 2.9
import Utils 1.0

Item {
    property int type: DeclarationType.None
    property string name: "Name"
    property string description: "Description"

    property real xPos: 0
    property real yPos: 0

    property real radius: 10
    property string color: "#03A9F4"

    property string borderColor: "#81D4FA"
    property int borderWidth: 2
}
