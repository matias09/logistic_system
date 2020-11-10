import QtQuick 2.9
import QtQuick.Controls 2.2
import LG 1.0
import assets 1.0
import components 1.0

Item {
    property Travel selectedTravel
    Component.onCompleted:
      masterController.ui_traCommandController.setSelectedTravel(selectedTravel)

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

                    ComboBox {
                      id: driver

                      anchors { fill: parent }

                      valueRole: "ui_value"
                      textRole: "ui_desc"
                      model: masterController.ui_traCommandController.ui_drivers

                      onActivated: {
                        selectedTravel.ui_destiny.ui_id_dri.ui_value = currentValue
                      }

                      Component.onCompleted: {
                        currentIndex = ( selectedTravel.ui_destiny.ui_id_dri.ui_value  )
                                        ?  indexOfValue(selectedTravel.ui_destiny.ui_id_dri.ui_value)
                                        :  indexOfValue(1)
                        selectedTravel.ui_destiny.ui_id_dri.ui_value = currentValue
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

                    ComboBox {
                      id: vehicle

                      anchors { fill: parent }

                      valueRole: "ui_value"
                      textRole: "ui_desc"
                      model: masterController.ui_traCommandController.ui_vehicles

                      onActivated: {
                        selectedTravel.ui_destiny.ui_id_veh.ui_value = currentValue
                      }

                      Component.onCompleted: {
                        currentIndex = ( selectedTravel.ui_destiny.ui_id_veh.ui_value  )
                                        ?  indexOfValue(selectedTravel.ui_destiny.ui_id_veh.ui_value)
                                        :  indexOfValue(1)
                        selectedTravel.ui_destiny.ui_id_veh.ui_value = currentValue
                      }
                    }
                  }
                }


              StringEditorSingleLine {
                stringDecorator: selectedTravel.ui_sta_date
                anchors {
                  left: parent.left
                  right: parent.right
                }
              }

              StringEditorSingleLine {
                stringDecorator: selectedTravel.ui_destiny.ui_arr_date
                anchors {
                  left: parent.left
                  right: parent.right
                }
              }
            }
          }

        AddressEditor {
          address: selectedTravel.ui_destiny.ui_address
          headerText: "Direccion de Destino"
        }
      }
  }

  CommandBar {
    id: commandList
    commandList:
      masterController.ui_traCommandController.ui_editTravelViewContextCommands
  }
}

