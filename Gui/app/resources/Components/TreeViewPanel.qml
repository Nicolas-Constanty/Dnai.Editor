import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQml.Models 2.3
import DNAI 1.0
import DNAI.Models 1.0

import "../Panels"
import "../Style"

ExpendablePanel {
    id: _panel
    title: qsTr("TreeViewPanel")
    property alias treeview: tr
    property variant last: undefined
    TreeView {
        id: tr

        anchors.fill: parent
        model: Editor.solution
        selection: ItemSelectionModel {
            model: Editor.solution
        }

        frameVisible: false
        TableViewColumn {
            role: "name"
        }
        style: TreeViewStyle {
            alternateBackgroundColor : AppSettings.theme["colors"]["background"]["dark"]
            backgroundColor : AppSettings.theme["colors"]["background"]["dark"]
            highlightedTextColor : AppSettings.theme["text"]["lightColor"]
            textColor : AppSettings.theme["text"]["color"]
        }
        onClicked: {
            Manager.views.updateNamespace(index)
        }

        Component.onCompleted: {
            _panel.last = currentIndex
        }

        headerVisible: false
    }
}
