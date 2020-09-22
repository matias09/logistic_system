import QtQuick 2.9
import assets 1.0

Item {
   property bool isCollapsed: true

  id: navigationBar
  anchors {
    top: parent.top
    bottom: parent.bottom
    left:  parent.left
  }
  width: isCollapsed ? Style.widthNavigationBarCollapsed : Style.heightNavigationBarExpanded

  Rectangle {
    color: Style.colourNavigationBarBackground
      width: parent.width

    Column {
      anchors.fill:  parent
      width: parent.width

      NavigationButton {
        iconCharacter: "\uf0c9"
        description: ""
        hoverColour: "#993333"
        onNavigationButtonClicked: isCollapsed = !isCollapsed
      }

      NavigationButton {
        iconCharacter: "\uf015"
        description: "Inicio"
        hoverColour: "#dc8a00"
        onNavigationButtonClicked: masterController.ui_navigationController.goDashboardView();
      }

      NavigationButton {
        iconCharacter: "\uf234"
        description: "Nuevo Cliente"
        hoverColour: "#dccd00"
        onNavigationButtonClicked:
            masterController.ui_navigationController.goCreateClientView();
      }

      NavigationButton {
        iconCharacter: "\uf002"
        description: "Buscar Cliente"
        hoverColour: "#8aef63"
        onNavigationButtonClicked:
            masterController.ui_navigationController.goFindClientView();
      }
    }
  }
}
