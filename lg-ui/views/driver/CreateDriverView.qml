import QtQuick 2.9
import QtQuick.Controls 1.4
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

    ScrollView {
      width:  900
      height: 300
      clip: true

      ScrollBar.vertical.policy: ScrollBar.AlwaysOn

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


          Flow {
            id: licFlow

            Rectangle {
              id: licLabelBackground
              width: Style.widthDataControls
              height: Style.heightDataControls
              color: Style.colourBackground

              Text {
                id: licDateLabel
                anchors {
                  fill: parent
                  margins: Style.heightDataControls / 4
                }
                text: newDriver.ui_lic_cad.ui_label
                color: Style.colourDataControlsFont
                font.pixelSize: Style.pixelSizeDataControls
                verticalAlignment: Qt.AlignVCenter
              }
            }

            CheckBox {
              id: licCalEnable
              checked: false

              anchors {
                right: licLabelBackground.right
                margins: Style.heightDataControls / 4
              }
            }

            Rectangle {
              id: licValueBackground
              width: Style.widthDataControls
              height: Style.heightDataControls
              color: Style.colourDataControlsBackground
              border {
                width: 1
                color: Style.colourDataControlsFont
              }

              TextInput {
                id: textValue
                anchors {
                  fill:parent
                  margins: Style.heightDataControls / 4
                }
                text: Qt.formatDate(newDriver.ui_lic_cad.ui_value
                                  , "yyyy-MM-dd")
                color: Style.colourDataControlsFont
                font.pixelSize: Style.pixelSizeDataControls
                verticalAlignment: Qt.AlignVCenter
              }
            }
          }

          Calendar {
            visible: licCalEnable.checked
            minimumDate: new Date(2020, 0, 1)
            maximumDate: new Date(2025, 0, 1)

            anchors {
              horizontalCenter: licFlow.horizontalCenter
              margins: Style.heightDataControls / 4
            }

            onClicked: {
              newDriver.ui_lic_cad.ui_value = selectedDate
              licCalEnable.checked = false
            }

            Component.onCompleted: {
              newDriver.ui_lic_cad.ui_value = selectedDate
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
