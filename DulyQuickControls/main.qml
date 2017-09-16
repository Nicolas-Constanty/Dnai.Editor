import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.2
import QtQuick.Dialogs 1.2
import "Resources/Components"

ApplicationWindow {
    visible: true
    width: 1280
    height: 720
    minimumHeight: 150
    minimumWidth: 300
    title: qsTr("Dully")
    Material.theme: Material.Dark
    Material.accent: Material.color(Material.DeepOrange, Material.Shade400)

    header: ToolBarHeader {}

}
