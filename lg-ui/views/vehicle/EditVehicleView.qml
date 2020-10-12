import QtQuick 2.9
import QtQuick.Controls 2.2
import LG 1.0
import assets 1.0
import components 1.0

Item {
    property Vehicle selectedVehicle
    Component.onCompleted:
      masterController.ui_vehCommandController.setSelectedVehicle(selectedVehicle)

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
        headerText: "Detalles del Vehiculo"
          contentComponent:
            Column {
              spacing: Style.sizeControlSpacing

              StringEditorSingleLine {
                stringDecorator: selectedVehicle.ui_reference
                anchors {
                  left: parent.left
                  right: parent.right
                }
                enabled: false
              }

              StringEditorSingleLine {
                stringDecorator: selectedVehicle.ui_type
                anchors {
                  left: parent.left
                  right: parent.right
                }
              }

              StringEditorSingleLine {
                stringDecorator: selectedVehicle.ui_brand
                anchors {
                  left: parent.left
                  right: parent.right
                }
              }

              StringEditorSingleLine {
                stringDecorator: selectedVehicle.ui_model
                anchors {
                  left: parent.left
                  right: parent.right
                }
              }

              StringEditorSingleLine {
                stringDecorator: selectedVehicle.ui_max_w
                anchors {
                  left: parent.left
                  right: parent.right
                }
              }

              StringEditorSingleLine {
                stringDecorator: selectedVehicle.ui_vin
                anchors {
                  left: parent.left
                  right: parent.right
                }
              }

              StringEditorSingleLine {
                stringDecorator: selectedVehicle.ui_vin_cad
                anchors {
                  left: parent.left
                  right: parent.right
                }
              }

              StringEditorSingleLine {
                stringDecorator: selectedVehicle.ui_year
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
      masterController.ui_vehCommandController.ui_editVehicleViewContextCommands
  }
}

