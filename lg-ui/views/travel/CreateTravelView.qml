import QtQuick 2.9
import QtQuick.Controls 2.2
import LG 1.0
import assets 1.0
import components 1.0

Item {
    property Travel newTravel: masterController.ui_newTravel

    Column {
      spacing:  Style.sizeScreenMargin
      anchors {
        left:      parent.left
        right:     parent.right
        top:       parent.top
        margins:   Style.sizeScreenMargin
      }

      Panel {
        headerText: "Detalles del Viaje"
        contentComponent:
          Column {
            spacing: Style.sizeControlSpacing

            StringEditorSingleLine {
              stringDecorator: newTravel.ui_id_cli
              anchors {
                left: parent.left
                right: parent.right
              }
            }

            StringEditorSingleLine {
              stringDecorator: newTravel.ui_sta_date
              anchors {
                left: parent.left
                right: parent.right
              }
            }

            StringEditorSingleLine {
              stringDecorator: newTravel.ui_destiny.ui_id_dri
              anchors {
                left: parent.left
                right: parent.right
              }
            }

            StringEditorSingleLine {
              stringDecorator: newTravel.ui_destiny.ui_id_veh
              anchors {
                left: parent.left
                right: parent.right
              }
            }

            StringEditorSingleLine {
              stringDecorator: newTravel.ui_destiny.ui_arr_date
              anchors {
                left: parent.left
                right: parent.right
              }
            }
          }
        }

        AddressEditor {
          address: newTravel.ui_destiny.ui_address
          headerText: "Direccion de Destino"
        }
    }

    CommandBar {
      id: commandList
      commandList:
        masterController.ui_traCommandController.ui_createTravelViewContextCommands
    }
}
