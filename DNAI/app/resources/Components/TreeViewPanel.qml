import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQml.Models 2.3
import DNAI 1.0

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

            var indexModel = Manager.getIndexMatch(cur)
            Manager.selectTreeItem(indexModel)
            Manager.updateNamespace(indexModel)
//            tr.selection.select(cur, ItemSelectionModel.ClearAndSelect)
            tr.selection.setCurrentIndex(indexModel, ItemSelectionModel.ClearAndSelect)
        }
        function changeCurrentFromModel(cur)
        {
            var indexModel = Manager.getIndexMatchFromModel(cur)
            Manager.selectTreeItem(indexModel)
            Manager.updateNamespace(indexModel)
            tr.selection.setCurrentIndex(indexModel, ItemSelectionModel.ClearAndSelect)
        }

        anchors.fill: parent
        model: Manager.projectModel
        selection: ItemSelectionModel {
            model: Manager.projectModel
        }

        frameVisible: false
        TableViewColumn {
            role: "name"
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

        Component.onCompleted: {
            _panel.last = currentIndex
        }

        headerVisible: false
    }
}
