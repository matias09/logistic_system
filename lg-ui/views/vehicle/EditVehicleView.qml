import QtQuick 2.9
import QtQuick.Controls 2.2
import LG 1.0
import assets 1.0
import components 1.0

Item {
    property Vehicle selectedVehicle
    Component.onCompleted:
      masterController.ui_vehCommandController.setSelectedVehicle(selectedVehicle)

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
        headerText: "Detalles del Vehiculo"
          contentComponent:
            Column {
              spacing: Style.sizeControlSpacing


              StringEditorSingleLine {
                stringDecorator: selectedVehicle.ui_reference
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
                  id: types_textLabel
                  anchors {
                    fill: parent
                    margins: Style.heightDataControls / 4
                  }
                  text: selectedVehicle.ui_id_type.ui_label
                  color: Style.colourDataControlsFont
                  font.pixelSize: Style.pixelSizeDataControls
                  verticalAlignment: Qt.AlignVCenter
                }
              }

              Rectangle {
                id: types_background
                width: Style.widthDataControls
                height: Style.heightDataControls
                border {
                  width: 1
                  color: Style.colourDataControlsFont
                }

                ComboBox {
                  id: types

                  anchors { fill: parent }

                  valueRole: "ui_value"
                  textRole: "ui_desc"
                  model: masterController.ui_vehCommandController.ui_types

                  onActivated: {
                    selectedVehicle.ui_id_type.ui_value = currentValue
                  }

                  Component.onCompleted: {
                    currentIndex = ( selectedVehicle.ui_id_type.ui_value  )
                                    ?  selectedVehicle.ui_id_type.ui_value - 1
                                    :  indexOfValue(1)
                    selectedVehicle.ui_id_type.ui_value = currentValue
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
                  id: brands_textLabel
                  anchors {
                    fill: parent
                    margins: Style.heightDataControls / 4
                  }
                  text: selectedVehicle.ui_id_brand.ui_label
                  color: Style.colourDataControlsFont
                  font.pixelSize: Style.pixelSizeDataControls
                  verticalAlignment: Qt.AlignVCenter
                }
              }

              Rectangle {
                id: brands_background
                width: Style.widthDataControls
                height: Style.heightDataControls
                border {
                  width: 1
                  color: Style.colourDataControlsFont
                }

                ComboBox {
                  id: brands

                  anchors { fill: parent }

                  valueRole: "ui_value"
                  textRole: "ui_desc"
                  model: masterController.ui_vehCommandController.ui_brands

                  onActivated: {
                    selectedVehicle.ui_brand.ui_value = currentValue
                  }

                  Component.onCompleted: {
                    currentIndex = ( selectedVehicle.ui_brand.ui_value  )
                                    ?  selectedVehicle.ui_brand.ui_value - 1
                                    :  indexOfValue(1)
                    selectedVehicle.ui_brand.ui_value = currentValue
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
                  id: models_textLabel
                  anchors {
                    fill: parent
                    margins: Style.heightDataControls / 4
                  }
                  text: selectedVehicle.ui_id_model.ui_label
                  color: Style.colourDataControlsFont
                  font.pixelSize: Style.pixelSizeDataControls
                  verticalAlignment: Qt.AlignVCenter
                }
              }

              Rectangle {
                id: models_background
                width: Style.widthDataControls
                height: Style.heightDataControls
                border {
                  width: 1
                  color: Style.colourDataControlsFont
                }

                ComboBox {
                  id: models

                  anchors { fill: parent }

                  valueRole: "ui_value"
                  textRole: "ui_desc"
                  model: masterController.ui_vehCommandController.ui_models

                  onActivated: {
                    selectedVehicle_ui_model.ui_value = currentValue
                  }

                  Component.onCompleted: {
                    currentIndex = ( selectedVehicle_ui_model.ui_value  )
                                    ?  selectedVehicle_ui_model.ui_value - 1
                                    :  indexOfValue(1)
                    selectedVehicle_ui_model.ui_value = currentValue
                  }
                }
              }
            }






              StringEditorSingleLine {
                stringDecorator: selectedVehicle.ui_max_w
                anchors {
                  left: parent.left
                  right: parent.right
                }
              }

              StringEditorSingleLine {
                stringDecorator: selectedVehicle.ui_vin
                anchors {
                  left: parent.left
                  right: parent.right
                }
              }

              StringEditorSingleLine {
                stringDecorator: selectedVehicle.ui_vin_cad
                anchors {
                  left: parent.left
                  right: parent.right
                }
              }

              StringEditorSingleLine {
                stringDecorator: selectedVehicle.ui_year
                anchors {
                  left: parent.left
                  right: parent.right
                }
              }
            }
          }
      }
  }

  CommandBar {
    id: commandList
    commandList:
      masterController.ui_vehCommandController.ui_editVehicleViewContextCommands
  }
}

