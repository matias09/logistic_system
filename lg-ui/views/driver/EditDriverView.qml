import QtQuick 2.9
import QtQuick.Controls 2.2
import LG 1.0
import assets 1.0
import components 1.0

Item {
    property Driver selectedDriver
    Component.onCompleted:
      masterController.ui_driCommandController.setSelectedDriver(selectedDriver)

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
        headerText: "Detalles del Chofer"
          contentComponent:
            Column {
              spacing: Style.sizeControlSpacing

              StringEditorSingleLine {
                stringDecorator: selectedDriver.ui_reference
                anchors {
                  left: parent.left
                  right: parent.right
                }
                enabled: false
              }

              StringEditorSingleLine {
                stringDecorator: selectedDriver.ui_name
                anchors {
                  left: parent.left
                  right: parent.right
                }
              }

              StringEditorSingleLine {
                stringDecorator: selectedDriver.ui_lic_nro
                anchors {
                  left: parent.left
                  right: parent.right
                }
              }

              StringEditorSingleLine {
                stringDecorator: selectedDriver.ui_lic_cad
                anchors {
                  left: parent.left
                  right: parent.right
                }
              }

              StringEditorSingleLine {
                stringDecorator: selectedDriver.ui_phone
                anchors {
                  left: parent.left
                  right: parent.right
                }
              }

              StringEditorSingleLine {
                stringDecorator: selectedDriver.ui_cellphone
                anchors {
                  left: parent.left
                  right: parent.right
                }
              }

              StringEditorSingleLine {
                stringDecorator: selectedDriver.ui_mail
                anchors {
                  left: parent.left
                  right: parent.right
                }
              }
            }
          }

          AddressEditor {
            address: selectedDriver.ui_driverAddress
            headerText: "Datos de Direccion"
          }
      }
  }

  CommandBar {
    id: commandList
    commandList:
      masterController.ui_driCommandController.ui_editDriverViewContextCommands
  }
}

