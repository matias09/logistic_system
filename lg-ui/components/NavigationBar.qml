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
        iconCharacter: "\uf007"
        description: "Clientes"
        hoverColour: "#8aef63"
        onNavigationButtonClicked:
            masterController.ui_navigationController.goFindClientView();
      }

      NavigationButton {
        iconCharacter: "\uf2bb"
        description: "Choferes"
        hoverColour: "#f55a63"
        onNavigationButtonClicked:
            masterController.ui_navigationController.goFindDriverView();
      }

      NavigationButton {
        iconCharacter: "\uf1b9"
        description: "Vehiculos"
        hoverColour: "#77ccaa"
        onNavigationButtonClicked:
            masterController.ui_navigationController.goFindVehicleView();
      }

      NavigationButton {
        iconCharacter: "\uf48B"
        description: "Viajes"
        hoverColour: "#7ac0f8"
        onNavigationButtonClicked:
            masterController.ui_navigationController.goFindTravelView();
      }

      NavigationButton {
        iconCharacter: "\uf2f5"
        description: "Exit"
        hoverColour: "#44403f"
        onNavigationButtonClicked: Qt.quit();
      }
    }
  }
}
