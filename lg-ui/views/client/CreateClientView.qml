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


    ComboBox {
      id: countries
      width: 300
      height: 25
      anchors {
        margins: Style.heightDataControls / 4
      }

      textRole: "text"
      valueRole: "value"
      // When an item is selected, update the backend.
      onActivated: t.text = currentValue
      // Set the initial currentIndex to the value stored in the backend.
      Component.onCompleted: {
        currentIndex = indexOfValue(1)

      }

      model: [
        { value: 0, text: qsTr("No modifier") },
        { value: 1, text: qsTr("Shift") },
        { value: 2, text: qsTr("Control") }
      ]
    }

    Text { id: t; anchors.top: countries.bottom }

    ListView {
      id: lv
      anchors.top: t.bottom
      model: [ "2323", "111" ]
      delegate: Rectangle {
        width: 150
        height: td.implicitHeight + 30

        Text {
          id: td
          width: parent.width
          height: parent.height
          text : modelData
        }
      }
    }
  }

  CommandBar {
    id: commandList
    commandList:
    masterController.ui_cliCommandController.ui_createClientViewContextCommands
  }
}
