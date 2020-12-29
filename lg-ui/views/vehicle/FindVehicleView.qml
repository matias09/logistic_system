import QtQuick 2.9
import assets 1.0
import LG 1.0
import components 1.0

Item {
  property VehicleSearch vehicleSearch: masterController.ui_vehicleSearch

  Rectangle {
    anchors.fill: parent
    color: Style.colourBackground

    Panel {
      id: searchPanel
      anchors {
        left: parent.left
        right: parent.right
        top: parent.top

        margins: Style.sizeScreenMargin
      }
      headerText: "Vehicle Search"

      contentComponent:
        StringEditorSingleLine {
          stringDecorator: vehicleSearch.ui_searchText
          anchors {
            left:  parent.left
            right: parent.right
          }
        }
    }

    ListView {
      id: itemsView
      anchors {
        top:    searchPanel.bottom
        left:   parent.left
        right:  parent.right
        bottom: parent.bottom

        margins: Style.sizeScreenMargin
      }
      clip: true
      model: vehicleSearch.ui_searchResults
      delegate: VehSearchResultDelegate {
        vehicle: modelData
      }
    }
  }

  CommandBar {
    commandList:
      masterController.ui_vehCommandController.ui_findVehicleViewContextCommands
  }
}
