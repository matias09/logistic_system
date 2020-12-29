import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQuick.Controls 2.2
import LG 1.0
import assets 1.0
import components 1.0

Item {
  property Driver selectedDriver
  Component.onCompleted:
  masterController.ui_driCommandController.setSelectedDriver(selectedDriver)

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
        headerText: "Driver Details"
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
            stringDecorator: selectedDriver.ui_nro_tra
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
                text: selectedDriver.ui_lic_cad.ui_label
                color: Style.colourDataControlsFont
                font.pixelSize: Style.pixelSizeDataControls
                verticalAlignment: Qt.AlignVCenter
              }

              CheckBox {
                id: licCalEnable
                checked: false

                anchors {
                  right: licLabelBackground.right
                  margins: Style.heightDataControls / 4
                }
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
                enabled: false
                anchors {
                  fill:parent
                  margins: Style.heightDataControls / 4
                }
                text: Qt.formatDate(selectedDriver.ui_lic_cad.ui_value
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
              selectedDriver.ui_lic_cad.ui_value = selectedDate
              licCalEnable.checked = false
            }

            selectedDate: selectedDriver.ui_lic_cad.ui_value
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
    }

    AddressEditor {
      address: selectedDriver.ui_driverAddress
      headerText: "Address Data"
    }

    Rectangle {
      id: recErr
      visible: (selectedDriver.ui_err.ui_value !== "")
      ? true : false;

      anchors {
        left: parent.left
        right: parent.right
      }

      width: Style.widthDataControls
      height: Style.heightDataControls
      color: "#ca4949"

      Text {
        id: errMessages

        anchors.fill: parent
        verticalAlignment: Text.AlignVCenter

        text: selectedDriver.ui_err.ui_value
        font.bold: true
        color: "#444444"
      }
    }
  }

  CommandBar {
    id: commandList
    commandList:
    masterController.ui_driCommandController.ui_editDriverViewContextCommands
  }
}

