import QtQuick 2.9
import QtQuick.Controls 2.2
import LG 1.0
import assets 1.0
import components 1.0

Item {
    property Travel newTravel: masterController.ui_newTravel

    Column {
      spacing:  Style.sizeScreenMargin
      anchors {
        left:      parent.left
        right:     parent.right
        top:       parent.top
        margins:   Style.sizeScreenMargin
      }

      Panel {
        headerText: "Detalles del Viaje"
        contentComponent:
          Column {
            spacing: Style.sizeControlSpacing


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
                    text: newTravel.ui_id_cli.ui_label
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
                      newTravel.ui_id_cli.ui_value = currentValue
                    }

                    Component.onCompleted: {
                      currentIndex = ( newTravel.ui_id_cli.ui_value  )
                                      ?  indexOfValue(newTravel.ui_id_cli.ui_value)
                                      :  indexOfValue(1)
                      newTravel.ui_id_cli.ui_value = currentValue
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
                    text: newTravel.ui_destiny.ui_id_dri.ui_label
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
                      newTravel.ui_destiny.ui_id_dri.ui_value = currentValue
                    }

                    Component.onCompleted: {
                      currentIndex = ( newTravel.ui_destiny.ui_id_dri.ui_value  )
                                      ?  indexOfValue(newTravel.ui_destiny.ui_id_dri.ui_value)
                                      :  indexOfValue(1)
                      newTravel.ui_destiny.ui_id_dri.ui_value = currentValue
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
                    text: newTravel.ui_destiny.ui_id_veh.ui_label
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
                      newTravel.ui_destiny.ui_id_veh.ui_value = currentValue
                    }

                    Component.onCompleted: {
                      currentIndex = ( newTravel.ui_destiny.ui_id_veh.ui_value  )
                                      ?  indexOfValue(newTravel.ui_destiny.ui_id_veh.ui_value)
                                      :  indexOfValue(1)
                      newTravel.ui_destiny.ui_id_veh.ui_value = currentValue
                    }
                  }
                }
              }









            StringEditorSingleLine {
              stringDecorator: newTravel.ui_sta_date
              anchors {
                left: parent.left
                right: parent.right
              }
            }

            StringEditorSingleLine {
              stringDecorator: newTravel.ui_destiny.ui_arr_date
              anchors {
                left: parent.left
                right: parent.right
              }
            }
          }
        }

        AddressEditor {
          address: newTravel.ui_destiny.ui_address
          headerText: "Direccion de Destino"
        }
    }

    CommandBar {
      id: commandList
      commandList:
        masterController.ui_traCommandController.ui_createTravelViewContextCommands
    }
}
