import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import Utils 1.0

import "../Panels"
import "../Style"

ExpendablePanel {
    title: qsTr("TreeViewPanel")
    property alias treeview: tr
    TreeView {
        id: tr
        function changeCurrent(cur)
        {
            console.log(cur)
            tr.selection.select(cur)
            Manager.selectTreeItem(cur)
        }
        anchors.fill: parent
        model: Manager.projectModel
        frameVisible: false
        TableViewColumn {
            role: "display"
        }
        style: TreeViewStyle {
            alternateBackgroundColor : DulySettings.style.background.darkColor
            backgroundColor : DulySettings.style.background.darkColor
            highlightedTextColor : DulySettings.style.text.lightColor
            textColor : DulySettings.style.text.color
        }
        onClicked: {
            Manager.updateNamespace(index)
        }
        headerVisible: false
    }
}
