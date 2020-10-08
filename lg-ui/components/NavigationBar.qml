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
        iconCharacter: "\uf0f2"
        description: "Clientes"
        hoverColour: "#8aef63"
        onNavigationButtonClicked:
            masterController.ui_navigationController.goFindClientView();
      }

      NavigationButton {
        iconCharacter: "\uf0c0"
        description: "Choferes"
        hoverColour: "#ffaa63"
        onNavigationButtonClicked:
            masterController.ui_navigationController.goFindDriverView();
      }
    }
  }
}
