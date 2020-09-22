import QtQuick 2.9
import QtQuick.Controls 2.2
import LG 1.0
import assets 1.0
import components 1.0

Item {
    property Client selectedClient
    Component.onCompleted:
      masterController.ui_commandController.setSelectedClient(selectedClient)

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
        bottom: commandBar.top

        margins:   Style.sizeScreenMargin
      }
      clip: true

      Column {
        spacing:  Style.sizeScreenMargin
        width: scrollView.width

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

          AddressEditor {
            address: selectedClient.ui_clientAddress
            headerText: "Datos de Direccion"
          }
      }
  }

  CommandBar {
    id: commandList
    commandList:
      masterController.ui_commandController.ui_editClientViewContextCommands
  }
}

