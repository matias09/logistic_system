import QtQuick 2.9
import QtQuick.Controls 2.2
import LG 1.0
import assets 1.0
import components 1.0

Item {
  property Client newClient: masterController.ui_newClient

  Column {
    spacing:  Style.sizeScreenMargin
    anchors {
      left:      parent.left
      right:     parent.right
      top:       parent.top
      margins:   Style.sizeScreenMargin
    }

    ScrollView {
      width:  900
      height: 300
      clip: true

      ScrollBar.vertical.policy: ScrollBar.AlwaysOn

      Panel {
        headerText: "Detalles del Cliente"
        contentComponent:
        Column {
          spacing: Style.sizeControlSpacing

          StringEditorSingleLine {
            stringDecorator: newClient.ui_name
            anchors {
              left: parent.left
              right: parent.right
            }
          }

          StringEditorSingleLine {
            stringDecorator: newClient.ui_phone
            anchors {
              left: parent.left
              right: parent.right
            }
          }

          StringEditorSingleLine {
            stringDecorator: newClient.ui_cellphone
            anchors {
              left: parent.left
              right: parent.right
            }
          }

          StringEditorSingleLine {
            id: mail
            stringDecorator: newClient.ui_mail
            anchors {
              left: parent.left
              right: parent.right
            }
          }
        }
      }
    }

    AddressEditor {
      address: newClient.ui_clientAddress
      headerText: "Datos de Direccion"
    }

  }
  CommandBar {
    id: commandList
    commandList:
    masterController.ui_cliCommandController.ui_createClientViewContextCommands
  }
}
