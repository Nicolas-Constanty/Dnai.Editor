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
        function changeCurrent(cur)
        {

            var indexModel = Manager.views.getIndexMatch(cur)
            Manager.views.selectTreeItem(indexModel)
            Manager.views.updateNamespace(indexModel)
//            tr.selection.select(cur, ItemSelectionModel.ClearAndSelect)
            tr.selection.setCurrentIndex(indexModel, ItemSelectionModel.ClearAndSelect)
        }
        function changeCurrentFromModel(cur)
        {
            var indexModel = Manager.views.getIndexMatchFromModel(cur)
            Manager.views.selectTreeItem(indexModel)
            Manager.views.updateNamespace(indexModel)
            tr.selection.setCurrentIndex(indexModel, ItemSelectionModel.ClearAndSelect)
        }

        anchors.fill: parent
        model: Manager.project
        selection: ItemSelectionModel {
            model: Manager.project
        }

        frameVisible: false
        TableViewColumn {
            role: "name"
        }
        style: TreeViewStyle {
            alternateBackgroundColor : AppSettings.style.background.darkColor
            backgroundColor : AppSettings.style.background.darkColor
            highlightedTextColor : AppSettings.style.text.lightColor
            textColor : AppSettings.style.text.color
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
