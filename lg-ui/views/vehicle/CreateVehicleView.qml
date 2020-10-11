import QtQuick 2.9
import QtQuick.Controls 2.2
import LG 1.0
import assets 1.0
import components 1.0

Item {
    property Vehicle newVehicle: masterController.ui_newVehicle

    Column {
      spacing:  Style.sizeScreenMargin
      anchors {
        left:      parent.left
        right:     parent.right
        top:       parent.top
        margins:   Style.sizeScreenMargin
      }

      Panel {
        headerText: "Detalles del Vehiculo"
        contentComponent:
          Column {
            spacing: Style.sizeControlSpacing

            StringEditorSingleLine {
              stringDecorator: newVehicle.ui_type
              anchors {
                left: parent.left
                right: parent.right
              }
            }

            StringEditorSingleLine {
              stringDecorator: newVehicle.ui_brand
              anchors {
                left: parent.left
                right: parent.right
              }
            }

            StringEditorSingleLine {
              stringDecorator: newVehicle.ui_model
              anchors {
                left: parent.left
                right: parent.right
              }
            }

            StringEditorSingleLine {
              stringDecorator: newVehicle.ui_max_w
              anchors {
                left: parent.left
                right: parent.right
              }
            }

            StringEditorSingleLine {
              stringDecorator: newVehicle.ui_vin
              anchors {
                left: parent.left
                right: parent.right
              }
            }

            StringEditorSingleLine {
              stringDecorator: newVehicle.ui_vin_cad
              anchors {
                left: parent.left
                right: parent.right
              }
            }

            StringEditorSingleLine {
              stringDecorator: newVehicle.ui_year
              anchors {
                left: parent.left
                right: parent.right
              }
            }
          }
        }
    }

    CommandBar {
      id: commandList
      commandList:
        masterController.ui_cliCommandController.ui_createVehicleViewContextCommands
    }
}
