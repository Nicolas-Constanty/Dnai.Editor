import QtQuick 2.9
import "../Panels"
import "../Components"

Rectangle {
    id: layout
    property ToolBarHeader toolBarHeader: ToolBarHeader {}
    property ConsoleComponent debugConsole: ConsoleComponent {}
    property PanelLeft leftPanel: PanelLeft {}
    property PanelRight rightPanel: PanelRight {}
    property PanelTop topPanel: PanelTop {}
}
