import QtQuick 2.9
import assets 1.0
import LG 1.0
import components 1.0

Item {
  property ClientSearch clientSearch: masterController.ui_clientSearch

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
      headerText: "Client Search"

      contentComponent:
        StringEditorSingleLine {
          stringDecorator: clientSearch.ui_searchText
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
      model: clientSearch.ui_searchResults
      delegate: CliSearchResultDelegate {
        client: modelData
      }
    }
  }

  CommandBar {
    commandList:
      masterController.ui_cliCommandController.ui_findClientViewContextCommands
  }
}
