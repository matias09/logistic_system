import QtQuick 2.9
import QtQuick.Controls 2.2
import LG 1.0
import assets 1.0
import components 1.0

Item {
    property Client selectedClient
    Component.onCompleted:
      masterController.ui_cliCommandController.setSelectedClient(selectedClient)

      Column {
        spacing:  Style.sizeScreenMargin
        anchors {
          left:      parent.left
          right:     parent.right
          top:       parent.top
          margins:   Style.sizeScreenMargin
        }

        ScrollView {
          width: 900
          height: 300
          clip: true

          ScrollBar.vertical.policy: ScrollBar.AlwaysOn

          Panel {
          headerText: "Detalles del Cliente"
            contentComponent:
              Column {
                spacing: Style.sizeControlSpacing

                StringEditorSingleLine {
                  stringDecorator: selectedClient.ui_reference
                  anchors {
                    left: parent.left
                    right: parent.right
                  }
                  enabled: false
                }

                StringEditorSingleLine {
                  stringDecorator: selectedClient.ui_name
                  anchors {
                    left: parent.left
                    right: parent.right
                  }
                }

                StringEditorSingleLine {
                  stringDecorator: selectedClient.ui_phone
                  anchors {
                    left: parent.left
                    right: parent.right
                  }
                }

                StringEditorSingleLine {
                  stringDecorator: selectedClient.ui_cellphone
                  anchors {
                    left: parent.left
                    right: parent.right
                  }
                }

                StringEditorSingleLine {
                  stringDecorator: selectedClient.ui_mail
                  anchors {
                    left: parent.left
                    right: parent.right
                  }
                }
              }
            }
          }


          AddressEditor {
            address: selectedClient.ui_clientAddress
            headerText: "Datos de Direccion"
          }
      }

  CommandBar {
    id: commandList
    commandList:
      masterController.ui_cliCommandController.ui_editClientViewContextCommands
  }
}

