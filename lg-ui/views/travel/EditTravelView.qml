import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQuick.Controls 2.2
import LG 1.0
import assets 1.0
import components 1.0

Item {
  property Travel selectedTravel
  Component.onCompleted: {
    selectedTravel.ui_destiny.ui_err.ui_value = ""
    masterController.ui_traCommandController.setSelectedTravel(selectedTravel)
}

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
        headerText: "Detalles del Viaje"
        contentComponent:
        Column {
          spacing: Style.sizeControlSpacing

          StringEditorSingleLine {
            stringDecorator: selectedTravel.ui_reference
            anchors {
              left: parent.left
              right: parent.right
            }
            enabled: false
          }

            Flow {
              Rectangle {
                width: Style.widthDataControls
                height: Style.heightDataControls
                color: Style.colourBackground

                  Text {
                    id: endedLabel
                    anchors {
                      fill: parent
                      margins: Style.heightDataControls / 4
                    }
                    text: selectedTravel.ui_ended.ui_label
                    color: Style.colourDataControlsFont
                    font.pixelSize: Style.pixelSizeDataControls
                    verticalAlignment: Qt.AlignVCenter
                  }
                }

                CheckBox {
                  id: endedEnable
                  checked: selectedTravel.ui_ended.ui_value
                  enabled: !selectedTravel.ui_canceled.ui_value

                  onClicked: {
                    selectedTravel.ui_ended.ui_value = !selectedTravel.ui_ended.ui_value
                  }

                  Component.onCompleted: {
                    enabled = ! selectedTravel.ui_ended.ui_value
                  }
                }
              }


          Flow {
            Rectangle {
              width: Style.widthDataControls
              height: Style.heightDataControls
              color: Style.colourBackground

              Text {
                id: textLabel
                anchors {
                  fill: parent
                  margins: Style.heightDataControls / 4
                }
                text: selectedTravel.ui_id_cli.ui_label
                color: Style.colourDataControlsFont
                font.pixelSize: Style.pixelSizeDataControls
                verticalAlignment: Qt.AlignVCenter
              }
            }

            Rectangle {
              id: background
              width: Style.widthDataControls
              height: Style.heightDataControls
              border {
                width: 1
                color: Style.colourDataControlsFont
              }

              ComboBox {
                id: client
                enabled:  ( !selectedTravel.ui_canceled.ui_value
                         && !selectedTravel.ui_ended.ui_value ) ? true : false

                anchors { fill: parent }

                valueRole: "ui_value"
                textRole: "ui_desc"
                model: masterController.ui_traCommandController.ui_clients

                onActivated: {
                  selectedTravel.ui_id_cli.ui_value = currentValue
                }

                Component.onCompleted: {
                  currentIndex = ( selectedTravel.ui_id_cli.ui_value  )
                  ?  indexOfValue(selectedTravel.ui_id_cli.ui_value)
                  :  indexOfValue(1)
                  selectedTravel.ui_id_cli.ui_value = currentValue
                }
              }
            }
          }

          Flow {
            Rectangle {
              width: Style.widthDataControls
              height: Style.heightDataControls
              color: Style.colourBackground

              Text {
                id: dritextLabel
                anchors {
                  fill: parent
                  margins: Style.heightDataControls / 4
                }
                text: selectedTravel.ui_destiny.ui_id_dri.ui_label
                + "   - ( Actual :  "
                + selectedTravel.ui_destiny.ui_dri.ui_value
                + " )"
                color: Style.colourDataControlsFont
                font.pixelSize: Style.pixelSizeDataControls
                verticalAlignment: Qt.AlignVCenter
              }
            }

            Rectangle {
              id: dribackground
              width: Style.widthDataControls
              height: Style.heightDataControls
              border {
                width: 1
                color: Style.colourDataControlsFont
              }

              CheckBox {
                id: driverComboEnable
                checked: false
                enabled:  ( !selectedTravel.ui_canceled.ui_value
                         && !selectedTravel.ui_ended.ui_value ) ? true : false

                anchors {
                  right: driver.left

                  margins: 3
                }
              }

              ComboBox {
                id: driver
                enabled: driverComboEnable.checked

                anchors { fill: parent }

                valueRole: "ui_value"
                textRole: "ui_desc"
                model: masterController.ui_traCommandController.ui_drivers

                onActivated: {
                  selectedTravel.ui_destiny.ui_id_dri.ui_value = currentValue
                }
                onEnabledChanged: {
                  selectedTravel.ui_destiny.ui_id_dri.ui_value = currentValue
                }

                Component.onCompleted: {
                  currentIndex = 0
                }
              }
            }
          }


          Flow {
            Rectangle {
              width: Style.widthDataControls
              height: Style.heightDataControls
              color: Style.colourBackground

              Text {
                id: vehtextLabel
                anchors {
                  fill: parent
                  margins: Style.heightDataControls / 4
                }
                text: selectedTravel.ui_destiny.ui_id_veh.ui_label
                + "   - ( Actual :  "
                + selectedTravel.ui_destiny.ui_veh.ui_value
                + " )"
                color: Style.colourDataControlsFont
                font.pixelSize: Style.pixelSizeDataControls
                verticalAlignment: Qt.AlignVCenter
              }
            }

            Rectangle {
              id: vehbackground
              width: Style.widthDataControls
              height: Style.heightDataControls
              border {
                width: 1
                color: Style.colourDataControlsFont
              }

              CheckBox {
                id: vehicleComboEnable
                checked: false
                enabled:  ( !selectedTravel.ui_canceled.ui_value
                         && !selectedTravel.ui_ended.ui_value ) ? true : false

                anchors {
                  right: vehicle.left

                  margins: 3
                }
              }

              ComboBox {
                id: vehicle
                enabled: vehicleComboEnable.checked

                anchors { fill: parent }

                valueRole: "ui_value"
                textRole: "ui_desc"
                model: masterController.ui_traCommandController.ui_vehicles

                onActivated: {
                  selectedTravel.ui_destiny.ui_id_veh.ui_value = currentValue
                }
                onEnabledChanged: {
                  selectedTravel.ui_destiny.ui_id_veh.ui_value = currentValue
                }
                Component.onCompleted: {
                  currentIndex = 0
                }
              }
            }
          }


          Flow {
            id: staDateFlow

            Rectangle {
              id: staDateLabelBackground
              width: Style.widthDataControls
              height: Style.heightDataControls
              color: Style.colourBackground

              Text {
                id: staDateLabel
                anchors {
                  fill: parent
                  margins: Style.heightDataControls / 4
                }
                text: selectedTravel.ui_sta_date.ui_label
                color: Style.colourDataControlsFont
                font.pixelSize: Style.pixelSizeDataControls
                verticalAlignment: Qt.AlignVCenter
              }

              CheckBox {
                id: staCalEnable
                checked: false
                enabled:  ( !selectedTravel.ui_canceled.ui_value
                         && !selectedTravel.ui_ended.ui_value ) ? true : false

                anchors {
                  right: staDateLabelBackground.right
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
                id: statextValue
                enabled: false
                anchors {
                  fill:parent
                  margins: Style.heightDataControls / 4
                }
                text: Qt.formatDate(selectedTravel.ui_sta_date.ui_value
                                  , "yyyy-MM-dd")
                color: Style.colourDataControlsFont
                font.pixelSize: Style.pixelSizeDataControls
                verticalAlignment: Qt.AlignVCenter
              }
            }
          }

          Calendar {
            id: staCal
            visible: staCalEnable.checked
            minimumDate: new Date(2020, 0, 1)
            maximumDate: new Date(2025, 0, 1)

            anchors {
              horizontalCenter: staDateFlow.horizontalCenter
              margins: Style.heightDataControls / 4
            }

            selectedDate: selectedTravel.ui_sta_date.ui_value

            onClicked: {
              selectedTravel.ui_sta_date.ui_value = selectedDate
              staCalEnable.checked = false
            }

            Component.onCompleted: {
              selectedTravel.ui_sta_date.ui_value = selectedDate
            }
          }


          Flow {
            id: arrFlow

            Rectangle {
              id: arrLabelBackground
              width: Style.widthDataControls
              height: Style.heightDataControls
              color: Style.colourBackground

              Text {
                id: arrDateLabel
                anchors {
                  fill: parent
                  margins: Style.heightDataControls / 4
                }
                text: selectedTravel.ui_destiny.ui_arr_date.ui_label
                color: Style.colourDataControlsFont
                font.pixelSize: Style.pixelSizeDataControls
                verticalAlignment: Qt.AlignVCenter
              }

              CheckBox {
                id: arrCalEnable
                checked: false
                enabled:  ( !selectedTravel.ui_canceled.ui_value
                         && !selectedTravel.ui_ended.ui_value ) ? true : false

                anchors {
                  right: arrLabelBackground.right
                  margins: Style.heightDataControls / 4
                }
              }
            }

            Rectangle {
              id: arrValueBackground
              width: Style.widthDataControls
              height: Style.heightDataControls
              color: Style.colourDataControlsBackground
              border {
                width: 1
                color: Style.colourDataControlsFont
              }

              TextInput {
                id: arrtextValue
                enabled: false
                anchors {
                  fill:parent
                  margins: Style.heightDataControls / 4
                }
                text: Qt.formatDate(selectedTravel.ui_destiny.ui_arr_date.ui_value
                                  , "yyyy-MM-dd")
                color: Style.colourDataControlsFont
                font.pixelSize: Style.pixelSizeDataControls
                verticalAlignment: Qt.AlignVCenter
              }
            }
          }

          Calendar {
            id: arrCal
            visible: arrCalEnable.checked
            minimumDate: new Date(2020, 0, 1)
            maximumDate: new Date(2025, 0, 1)

            anchors {
              horizontalCenter: arrFlow.horizontalCenter
              margins: Style.heightDataControls / 4
            }

            selectedDate: selectedTravel.ui_destiny.ui_arr_date.ui_value

            onClicked: {
              selectedTravel.ui_destiny.ui_arr_date.ui_value = selectedDate
              arrCalEnable.checked = false
            }

            Component.onCompleted: {
              selectedTravel.ui_destiny.ui_arr_date.ui_value = selectedDate
            }
          }

          Binding {
            target: selectedTravel.ui_cli
            property: "ui_value"
            value: client.currentText
          }

        }
      }
    }

    AddressEditor {
      address: selectedTravel.ui_destiny.ui_address
      headerText: "Direccion de Destino"
      enabled:  ( !selectedTravel.ui_canceled.ui_value
               && !selectedTravel.ui_ended.ui_value ) ? true : false
    }

    Rectangle {
      id: recErr
      visible: (selectedTravel.ui_destiny.ui_err.ui_value !== "")
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

          text: selectedTravel.ui_destiny.ui_err.ui_value
          font.bold: true
          color: "#444444"
      }
    }
  }

  CommandBar {
    id: commandList
    commandList:
    masterController.ui_traCommandController.ui_editTravelViewContextCommands
  }
}

