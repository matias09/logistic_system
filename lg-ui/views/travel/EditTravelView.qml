import QtQuick 2.9
import QtQuick.Controls 2.2
import LG 1.0
import assets 1.0
import components 1.0

Item {
    property Travel selectedTravel
    Component.onCompleted:
      masterController.ui_traCommandController.setSelectedTravel(selectedTravel)

    Rectangle {
      anchors.fill: parent
      color: Style.colourBackground
    }

    ScrollView {
      id: scrollView
      anchors {
        left:      parent.left
        right:     parent.right
        top:       parent.top
        bottom:    commandBar.top

        margins:   Style.sizeScreenMargin
      }
      clip: true

      Column {
        spacing:  Style.sizeScreenMargin
        width: scrollView.width

        Panel {
        headerText: "Detalles del Viaje"
          contentComponent:
            Column {
              spacing: Style.sizeControlSpacing

              StringEditorSingleLine {
                stringDecorator: selectedTravel.ui_reference
                anchors {
                  left: parent.left
                  right: parent.right
                }
                enabled: false
              }

              StringEditorSingleLine {
                stringDecorator: selectedTravel.ui_type
                anchors {
                  left: parent.left
                  right: parent.right
                }
              }

              StringEditorSingleLine {
                stringDecorator: selectedTravel.ui_brand
                anchors {
                  left: parent.left
                  right: parent.right
                }
              }

              StringEditorSingleLine {
                stringDecorator: selectedTravel.ui_model
                anchors {
                  left: parent.left
                  right: parent.right
                }
              }

              StringEditorSingleLine {
                stringDecorator: selectedTravel.ui_max_w
                anchors {
                  left: parent.left
                  right: parent.right
                }
              }

              StringEditorSingleLine {
                stringDecorator: selectedTravel.ui_vin
                anchors {
                  left: parent.left
                  right: parent.right
                }
              }

              StringEditorSingleLine {
                stringDecorator: selectedTravel.ui_vin_cad
                anchors {
                  left: parent.left
                  right: parent.right
                }
              }

              StringEditorSingleLine {
                stringDecorator: selectedTravel.ui_year
                anchors {
                  left: parent.left
                  right: parent.right
                }
              }
            }
          }
      }
  }

  CommandBar {
    id: commandList
    commandList:
      masterController.ui_traCommandController.ui_editTravelViewContextCommands
  }
}

