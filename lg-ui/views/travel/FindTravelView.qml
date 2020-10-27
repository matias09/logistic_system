import QtQuick 2.9
import assets 1.0
import LG 1.0
import components 1.0

Item {
  property TravelSearch travelSearch: masterController.ui_travelSearch

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
      headerText: "Buscar Viaje"

      contentComponent:
        StringEditorSingleLine {
          stringDecorator: travelSearch.ui_searchText
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
      model: travelSearch.ui_searchResults
      delegate: TraSearchResultDelegate {
        travel: modelData
      }
    }
  }

  CommandBar {
    commandList:
      masterController.ui_traCommandController.ui_findTravelViewContextCommands
  }
}
