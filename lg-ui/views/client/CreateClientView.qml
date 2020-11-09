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

    AddressEditor {
      address: newClient.ui_clientAddress
      headerText: "Datos de Direccion"
    }


//    Text { id: t; anchors.top: bck_towns }
//
//    ComboBox {
//      id: bck_towns
//      width: 300
//      height: 25
//      anchors {
//        margins: Style.heightDataControls / 4
//      }
//
//      valueRole: "ui_value"
//      textRole: "ui_desc"
//
//      model: masterController.ui_towns
//
//      onActivated: {
//      newClient.ui_name.ui_value = currentValue
//        t.text = currentValue
//      }
//    onCurrentIndexChanged:  t2.text = currentIndex
//      Component.onCompleted: {
//        currentIndex = indexOfValue(1)
//      newClient.ui_name.ui_value = currentValue
//      }
//    }

  }

  CommandBar {
    id: commandList
    commandList:
    masterController.ui_cliCommandController.ui_createClientViewContextCommands
  }
}
