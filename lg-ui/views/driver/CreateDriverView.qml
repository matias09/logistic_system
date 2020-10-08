import QtQuick 2.9
import QtQuick.Controls 2.2
import LG 1.0
import assets 1.0
import components 1.0

Item {
    property Driver newDriver: masterController.ui_newDriver

    Column {
      spacing:  Style.sizeScreenMargin
      anchors {
        left:      parent.left
        right:     parent.right
        top:       parent.top
        margins:   Style.sizeScreenMargin
      }

      Panel {
        headerText: "Detalles del Chofer"
        contentComponent:
          Column {
            spacing: Style.sizeControlSpacing

            StringEditorSingleLine {
              stringDecorator: newDriver.ui_name
              anchors {
                left: parent.left
                right: parent.right
              }
            }

            StringEditorSingleLine {
              stringDecorator: newDriver.ui_lic_nro
              anchors {
                left: parent.left
                right: parent.right
              }
            }

            StringEditorSingleLine {
              stringDecorator: newDriver.ui_lic_cad
              anchors {
                left: parent.left
                right: parent.right
              }
            }

            StringEditorSingleLine {
              stringDecorator: newDriver.ui_phone
              anchors {
                left: parent.left
                right: parent.right
              }
            }

            StringEditorSingleLine {
              stringDecorator: newDriver.ui_cellphone
              anchors {
                left: parent.left
                right: parent.right
              }
            }

            StringEditorSingleLine {
              stringDecorator: newDriver.ui_mail
              anchors {
                left: parent.left
                right: parent.right
              }
            }
          }
        }

        AddressEditor {
          address: newDriver.ui_driverAddress
          headerText: "Datos de Direccion"
        }
    }

    CommandBar {
      id: commandList
      commandList:
        masterController.ui_driCommandController.ui_createDriverViewContextCommands
    }
}
